#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <sstream>
#include <exception>
#include <string>
#include <cstddef>
#include <iomanip>

#include <cuda_runtime.h>
#include <thrust/scan.h>

#include "../helpers.hpp"

namespace cpu {
    template <class T>
    void inclusive_scan(const T* RESTRICT input, T* RESTRICT output, int N)
    {
        output[0] = input[0];
        for (int i = 1; i < N; i++)
            output[i] = output[i - 1] + input[i];
    }

    template <class T>
    void inclusive_scan_stl(const T* RESTRICT input, T* RESTRICT output, int N)
    {
        std::inclusive_scan(input, input + N, output);
    }

    template <class T>
    void inclusive_scan_parallel(const T* RESTRICT input, T* RESTRICT output, int N)
    {
        constexpr int ELEMENTS_PER_ITERATION = 1024;

        auto blelloch_scan_power_of_2 = [](T* buffer) {
            // Up-Sweep Step:
            // indices:   0  1  2  3  4  5  6  7
            // input:     1  2  3  4  5  6  7  8        
            // skip-2:       3     7     11    15
            // skip-4:             10          26 
            // skip-8:                         36
            // up-sweeep: 1  3  3  10 5  11 7  36
            //
            // in skip-K, we access [K, K * 2, K * 3, ...] until we exceed N
            // in skip-K, the children of 'i' is 'i' and 'i' - K / 2

            for (int skip = 2; skip <= ELEMENTS_PER_ITERATION; skip *= 2)
                for (int i = skip - 1; i < ELEMENTS_PER_ITERATION; i += skip)
                    buffer[i] += buffer[i - skip / 2];

            auto total = buffer[ELEMENTS_PER_ITERATION - 1];
            buffer[ELEMENTS_PER_ITERATION - 1] = 0;

            // Down-Sweep Step (Exclusive Scan):
            // N = current node, LC(X) = left child of x, RC(X) = right child of X, M(X) = mirror node of X in the up-sweep tree
            //
            // New LC = N
            // New RC = N + LC(M(N))
            //
            // Trick 1: mirror node sits at the same index in the input
            // Trick 2: in skip-N, the right child is at the same index and left child is K indices behind
            // Trick 3: if you go a depth, you have to use skip-(K/2) for children; for example, LC(M(N)) is skip-(K/2) from M(N)
            // 
            // In summary, to recursively update, read N, save LC(M(N)) (K / 2 indices behind), update the LC(N) and then RC(N) (same index as N).
            // We save LC because it shares the index with LC(M(N))) which is required to compute RC(N).
            //
            // indices:    0  1  2  3  4  5  6  7
            // input:      1  3  3  10 5  11 7  36
            // preprocess: 1  3  3  10 5  11 7  0
            // skip-8:              0           10 (N = 0, LC(M(N)) = 10)      
            // skip-4:        0     3     10    21
            // skip-2:     0  1  3  6  10 15 21 28

            for(int skip = ELEMENTS_PER_ITERATION; skip > 1; skip /= 2)
            {
                for (int i = skip - 1; i < ELEMENTS_PER_ITERATION; i += skip)
                {
                    auto current = buffer[i];
                    auto lc_mirror = buffer[i - skip / 2];

                    buffer[i - skip / 2] = current;
                    buffer[i] = current + lc_mirror;
                }
            }

            // convert to inclusive scan
            for (int i = 1; i < ELEMENTS_PER_ITERATION; i++)
                buffer[i - 1] = buffer[i];
            buffer[ELEMENTS_PER_ITERATION - 1] = total;
            return total;
        };
        
        std::vector<T> sub_totals;
        int num_full_iterations = N / ELEMENTS_PER_ITERATION;
        for (int iter = 0; iter < num_full_iterations; iter++)
        {
            auto input_start = input + iter * ELEMENTS_PER_ITERATION;
            auto output_start = output + iter * ELEMENTS_PER_ITERATION;

            for (int i = 0; i < ELEMENTS_PER_ITERATION; i++)
                output_start[i] = input_start[i];
            
            auto sub_total = blelloch_scan_power_of_2(output_start);
            sub_totals.push_back(sub_total);
        }

        if (num_full_iterations * ELEMENTS_PER_ITERATION < N)
        {
            // scan trailing block
            auto starting_offset = num_full_iterations * ELEMENTS_PER_ITERATION;
            auto ending_offset = N;
            auto range_size = ending_offset - starting_offset;

            auto input_start = input + starting_offset;
            auto output_start = output + starting_offset;

            output_start[0] = input_start[0];
            for (int i = 1; i < range_size; i++)
                output_start[i] = output_start[i - 1] + input_start[i];
            sub_totals.push_back(output_start[range_size - 1]);
        }

        if (sub_totals.size() > 1)
        {
            inclusive_scan_parallel(sub_totals.data(), sub_totals.data(), sub_totals.size());
            for (int iter = 1; iter <= sub_totals.size(); iter++)
            {
                auto residual = sub_totals[iter - 1];

                auto starting_offset = iter * ELEMENTS_PER_ITERATION;
                auto ending_offset = min(N, starting_offset + ELEMENTS_PER_ITERATION);
                auto range_size = ending_offset - starting_offset;

                auto input_start = input + starting_offset;
                auto output_start = output + starting_offset;

                for (int i = 0; i < range_size; i++)
                    output_start[i] += residual;
            }
        }            
    }
}

namespace thrust_gpu {
    template <class T>
    void inclusive_scan(const T* CUDA_RESTRICT input, T* CUDA_RESTRICT output, int N)
    {
        thrust::plus<T> plus;
        thrust::inclusive_scan(thrust::device, input, input + N, output, plus);
    }
}

namespace gpu {

    template <class T>
    __global__
    void hillis_steele_scan(const T* CUDA_RESTRICT input, T* CUDA_RESTRICT buffer, T* CUDA_RESTRICT output, int N)
    {
        const T* buf_in = input;
        T* buf_out = buffer;
        for (int scanned_till = 1; scanned_till < N; scanned_till *= 2)
        {
            #pragma unroll 8
            for (int i = threadIdx.x; i < N; i += blockDim.x)
            {
                if (i < scanned_till)
                    buf_out[i] = buf_in[i];
                else
                    buf_out[i] = buf_in[i] + buf_in[i - scanned_till];
            }

            __syncthreads();

            if (buf_out == buffer)
            {
                buf_in = buffer;
                buf_out = output;
            }
            else
            {
                buf_in = output;
                buf_out = buffer;
            }
        }

        if (buf_in != output)
        {
            for (int i = threadIdx.x; i < N; i += blockDim.x)
                output[i] = buffer[i];
        }
    }

    template <class T>
    void inclusive_scan_v1(const T* d_input, T* d_output, int N)
    {
        T* buffer;
        CHECK_CUDA(cudaMalloc(&buffer, N * sizeof(T)));
        gpu::hillis_steele_scan<<<1, 1024>>>(d_input, buffer, d_output, N);
        CHECK_CUDA(cudaGetLastError());
        CHECK_CUDA(cudaFree(buffer));        
    }

    template <class T, int BLOCK_SIZE, int ELEMENTS_PER_ITERATION>
    __global__
    __launch_bounds__(BLOCK_SIZE)
    void blelloch_scan_power_of_2(const T* input, T* sub_totals, T* output, int N)
    {
        auto starting_offset = blockIdx.x * ELEMENTS_PER_ITERATION;
        auto ending_offset = min(N, starting_offset + ELEMENTS_PER_ITERATION);
        auto range_size = ending_offset - starting_offset;
  
        input += starting_offset;
        output += starting_offset;

        constexpr int NUM_BANKS = 32;
        __shared__ T buffer[ELEMENTS_PER_ITERATION + ELEMENTS_PER_ITERATION / NUM_BANKS];
        auto access_buffer = [](int idx) -> T& {
            return buffer[idx + (idx / NUM_BANKS)];
        };

        for (int i = threadIdx.x; i < ELEMENTS_PER_ITERATION; i += BLOCK_SIZE)
            access_buffer(i) = (i < range_size) ? input[i] : 0;        
   
        // Up-Sweep Step:
        // indices:   0  1  2  3  4  5  6  7
        // input:     1  2  3  4  5  6  7  8        
        // skip-2:       3     7     11    15
        // skip-4:             10          26 
        // skip-8:                         36
        // up-sweeep: 1  3  3  10 5  11 7  36
        //
        // in skip-K, we access [K, K * 2, K * 3, ...] until we exceed N
        // in skip-K, the children of 'i' is 'i' and 'i' - K / 2

        #pragma unroll
        for (int skip = 2; skip <= ELEMENTS_PER_ITERATION; skip *= 2)
        {
            __syncthreads();         
            for (int i = threadIdx.x; i < ELEMENTS_PER_ITERATION / skip; i += BLOCK_SIZE)
            {
                auto idx = (i + 1) * skip - 1;
                access_buffer(idx) += access_buffer(idx - skip / 2);
            }
        }

        T total = 0;
        if (threadIdx.x == 0)
        {
            total = access_buffer(ELEMENTS_PER_ITERATION - 1);
            access_buffer(ELEMENTS_PER_ITERATION - 1) = 0;
        }

        // Down-Sweep Step (Exclusive Scan):
        // N = current node, LC(X) = left child of x, RC(X) = right child of X, M(X) = mirror node of X in the up-sweep tree
        //
        // New LC = N
        // New RC = N + LC(M(N))
        //
        // Trick 1: mirror node sits at the same index in the input
        // Trick 2: in skip-N, the right child is at the same index and left child is K indices behind
        // Trick 3: if you go a depth, you have to use skip-(K/2) for children; for example, LC(M(N)) is skip-(K/2) from M(N)
        // 
        // In summary, to recursively update, read N, save LC(M(N)) (K / 2 indices behind), update the LC(N) and then RC(N) (same index as N).
        // We save LC because it shares the index with LC(M(N))) which is required to compute RC(N).
        //
        // indices:    0  1  2  3  4  5  6  7
        // input:      1  3  3  10 5  11 7  36
        // preprocess: 1  3  3  10 5  11 7  0
        // skip-8:              0           10 (N = 0, LC(M(N)) = 10)      
        // skip-4:        0     3     10    21
        // skip-2:     0  1  3  6  10 15 21 28

        #pragma unroll
        for(int skip = ELEMENTS_PER_ITERATION; skip > 1; skip /= 2)
        {
            __syncthreads();

            #pragma unroll
            for (int i = threadIdx.x; i < ELEMENTS_PER_ITERATION / skip; i += BLOCK_SIZE)
            {
                auto idx = (i + 1) * skip - 1;
                auto current = access_buffer(idx);
                auto lc_mirror = access_buffer(idx - skip / 2);

                access_buffer(idx - skip / 2) = current;
                access_buffer(idx)  = current + lc_mirror;
            }
        }

        __syncthreads();

        // convert to inclusive scan
        for (int i = threadIdx.x; i < range_size - 1; i += BLOCK_SIZE)
            output[i] = access_buffer(i + 1);

        if (threadIdx.x == 0)
        {
            output[range_size - 1] = total;
            if (sub_totals)
                sub_totals[blockIdx.x] = total;
        }        
    }

    template <class T, int BLOCK_SIZE, int ELEMENTS_PER_ITERATION>
    __global__
    void correct_block_scans(const T* input, const T* sub_totals, T* output, int N)
    {
        auto starting_offset = (blockIdx.x + 1) * ELEMENTS_PER_ITERATION;
        auto ending_offset = min(N, starting_offset + ELEMENTS_PER_ITERATION);
        auto range_size = ending_offset - starting_offset;

        input += starting_offset;
        output += starting_offset;

        auto residual = sub_totals[blockIdx.x];
        for (int i = threadIdx.x; i < range_size; i += BLOCK_SIZE)
            output[i] += residual;
    }

    template <class T>
    void inclusive_scan_v2(const T* input, T* output, int N)
    {
        constexpr int BLOCK_SIZE = 64;
        constexpr int ELEMENTS_PER_ITERATION = 512;

        int num_iterations = (N + ELEMENTS_PER_ITERATION - 1) / ELEMENTS_PER_ITERATION;
        T* sub_totals = nullptr;
        if (num_iterations > 1)
        {
            CHECK_CUDA(cudaMalloc(&sub_totals, num_iterations * sizeof(T)));
        }

        blelloch_scan_power_of_2<T, BLOCK_SIZE, ELEMENTS_PER_ITERATION><<<num_iterations, BLOCK_SIZE>>>(input, sub_totals, output, N);
        CHECK_CUDA(cudaGetLastError());

        if (num_iterations > 1)
        {
            inclusive_scan_v2(sub_totals, sub_totals, num_iterations);
            correct_block_scans<T, BLOCK_SIZE, ELEMENTS_PER_ITERATION><<<num_iterations - 1, BLOCK_SIZE>>>(input, sub_totals, output, N);
            CHECK_CUDA(cudaGetLastError());
            CHECK_CUDA(cudaDeviceSynchronize());
            CHECK_CUDA(cudaFree(sub_totals));
        }
    }
}

int main ()
{
    using T = double;
    const int N = 10'000'000;    

    constexpr float THRESHOLD = 0.001;
    
    std::vector<T> input(N);
    random_fill(std::begin(input), std::end(input));

    T* d_input, *d_output;
    CHECK_CUDA(cudaMalloc(&d_input, input.size() * sizeof(T)));
    CHECK_CUDA(cudaMalloc(&d_output, input.size() * sizeof(T)));

    std::vector<T> output_cpu(N);
    auto cpu_time = benchmark([&input, &output_cpu, N] {
        cpu::inclusive_scan_parallel(input.data(), output_cpu.data(), N);
    });
    std::cout << "[CPU] Running time: " << to_milliseconds(cpu_time).count() << "ms\n";
    std::cout << std::endl;

    std::vector<T> output_thrust(N);
    auto thrust_gpu_time = benchmark([&] {
        CHECK_CUDA(cudaMemcpy(d_input, input.data(), input.size() * sizeof(T), cudaMemcpyHostToDevice));
        thrust_gpu::inclusive_scan(d_input, d_output, N);
        CHECK_CUDA(cudaGetLastError());
        CHECK_CUDA(cudaMemcpy(output_thrust.data(), d_output, output_thrust.size() * sizeof(T), cudaMemcpyDeviceToHost));
    });
    std::cout << "[thrust] Running time (incl. memory copy): " << to_milliseconds(thrust_gpu_time).count() << "ms\n";
    print_result(std::begin(output_cpu), std::end(output_cpu), std::begin(output_thrust), THRESHOLD);
    std::cout << std::endl;

    // erase previous results
    CHECK_CUDA(cudaMemset(d_output, 0, input.size() * sizeof(T)));

    std::vector<T> output_gpu(N);
    auto gpu_time = benchmark([&] {
        CHECK_CUDA(cudaMemcpy(d_input, input.data(), input.size() * sizeof(T), cudaMemcpyHostToDevice));
        gpu::inclusive_scan_v2(d_input, d_output, N);
        CHECK_CUDA(cudaMemcpy(output_gpu.data(), d_output, output_gpu.size() * sizeof(T), cudaMemcpyDeviceToHost));
    });
    std::cout << "[GPU] Running time (incl. memory copy): " << to_milliseconds(gpu_time).count() << "ms" << std::endl;
    print_result(std::begin(output_cpu), std::end(output_cpu), std::begin(output_gpu), THRESHOLD);

    CHECK_CUDA(cudaFree(d_input));
    CHECK_CUDA(cudaFree(d_output));
    return 0;
}