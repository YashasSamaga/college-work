#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <sstream>
#include <exception>
#include <string>
#include <cstddef>

#include <cuda_runtime.h>

#include "../helpers.hpp"

/************************** SPMV IMPLEMENTATIONS BEGIN **********************/

namespace cpu_impl {
    template <class T>
    void spmv_csr(int M, int N, const int* RESTRICT row_ptr, const int* RESTRICT col_idxs, const T* RESTRICT values, const T* RESTRICT x, T* RESTRICT output)
    {
        for (int i = 0; i < M; i++)
        {
            // row i
            auto row_start = row_ptr[i];
            auto row_end = row_ptr[i + 1];

            T accumulator = 0;
            for (int idx = row_start; idx < row_end; idx++)
            {
                auto c = col_idxs[idx];
                auto v = values[idx];
                accumulator += v * x[c];
            }
            output[i] = accumulator;
        }
    }
}

namespace gpu_impl {

    template <class T> __device__ T load_streaming(T* x) { return *x; }
    template <> inline __device__ int load_streaming(int* x) {
        int value;
        asm("ld.global.cs.u32 %0, [%1];" : "=r"(value) : "l"(x));
        return value;
    }

    template <> inline __device__ float load_streaming(float* x) {
        float value;
        asm("ld.global.cs.f32 %0, [%1];" : "=f"(value) : "l"(x));
        return value;
    }

    template <> inline __device__ double load_streaming(double* x) {
        double value;
        asm("ld.global.cs.f64 %0, [%1];" : "=d"(value) : "l"(x));
        return value;
    }
 
    template <class T>
    __global__
    void spmv_csr(int M, int N, const int* CUDA_RESTRICT row_ptr, const int* CUDA_RESTRICT col_idxs, const T* CUDA_RESTRICT values, const T* CUDA_RESTRICT x, T* CUDA_RESTRICT output)
    {
        constexpr int WARP_SIZE = 32;

        int threadId = threadIdx.x + blockIdx.x * blockDim.x;
        int warpId = threadId / WARP_SIZE;
        int laneId = threadId  % WARP_SIZE;
        int num_warps = blockDim.x * gridDim.x / WARP_SIZE;

        #pragma unroll 1
        for (int i = warpId; i < M; i += num_warps)
        {
            // row i
            auto row_start = row_ptr[i];
            auto row_end = row_ptr[i + 1];

            T local_accumulator = 0;

            #pragma unroll 4
            for (int idx = row_start + laneId; idx < row_end; idx += WARP_SIZE)
            {
                auto c = col_idxs[idx];
                auto v = values[idx];
                local_accumulator += v * x[c];
            }

            auto total = warpReduceSum(local_accumulator);
            if (laneId == 0)
                output[i] = total;
        }
    }
}

/************************** SPMV IMPLEMENTATIONS END **********************/

int main ()
{
    using T = double;
    constexpr int M = 4096, N = 4096;

    constexpr T THRESHOLD = 1e-2;
    constexpr float SPARSITY = 0.9;

    // CSR faster for random sparse matrices
    std::vector<int> row_ptr, col_idxs;
    std::vector<T> values;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-1, 1);

    row_ptr.push_back(0);
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            auto prob = dist(gen);
            if (std::abs(prob) > SPARSITY)
            {
                col_idxs.push_back(j);
                values.push_back(dist(gen));
            }
        }
        row_ptr.push_back(values.size());
    }

    std::vector<T> x(N), output_cpu(N);
    random_fill(std::begin(x), std::end(x));

    int* d_row_ptr, *d_col_idxs;
    T *d_values;
    CHECK_CUDA(cudaMalloc(&d_row_ptr, row_ptr.size() * sizeof(int)));
    CHECK_CUDA(cudaMalloc(&d_col_idxs, col_idxs.size() * sizeof(int)));
    CHECK_CUDA(cudaMalloc(&d_values, values.size() * sizeof(T)));

    T* d_x;
    CHECK_CUDA(cudaMalloc(&d_x, x.size() * sizeof(T)));

    T* d_output;
    CHECK_CUDA(cudaMalloc(&d_output, output_cpu.size() * sizeof(T)));

    std::cout << "CPU Evaluation:\n";
    {
        auto cpu_time = benchmark([&] {
            cpu_impl::spmv_csr(M, N, row_ptr.data(), col_idxs.data(), values.data(), x.data(), output_cpu.data());
        });
        std::cout << "\tRunning time: " << to_milliseconds(cpu_time).count() << "ms\n";
    }
    std::cout << std::endl;

    std::vector<T> output_gpu(output_cpu.size());
    std::cout << "GPU Evaluation:\n";
    {
        auto cpu_time = benchmark([&] {
            CHECK_CUDA(cudaMemcpy(d_row_ptr, row_ptr.data(), row_ptr.size() * sizeof(int), cudaMemcpyHostToDevice));
            CHECK_CUDA(cudaMemcpy(d_col_idxs, col_idxs.data(), col_idxs.size() * sizeof(int), cudaMemcpyHostToDevice));
            CHECK_CUDA(cudaMemcpy(d_values, values.data(), values.size() * sizeof(T), cudaMemcpyHostToDevice));
            CHECK_CUDA(cudaMemcpy(d_x, x.data(), x.size() * sizeof(T), cudaMemcpyHostToDevice));

            int grid_size = 0, block_size = 0;
            CHECK_CUDA(cudaOccupancyMaxPotentialBlockSize(&grid_size, &block_size, gpu_impl::spmv_csr<T>, 0));
            gpu_impl::spmv_csr<<<grid_size, block_size>>>(M, N, d_row_ptr, d_col_idxs, d_values, d_x, d_output);

            CHECK_CUDA(cudaMemcpy(output_gpu.data(), d_output, output_gpu.size() * sizeof(T), cudaMemcpyDeviceToHost));
        });
        std::cout << "\tRunning time (incl. memory copy): " << to_milliseconds(cpu_time).count() << "ms\n" << std::endl;
    }
    auto pr = check_result(std::begin(output_cpu), std::end(output_cpu), std::begin(output_gpu), THRESHOLD);
    print_result(std::begin(output_cpu), std::end(output_cpu), std::begin(output_gpu), THRESHOLD);

    CHECK_CUDA(cudaFree(d_row_ptr));
    CHECK_CUDA(cudaFree(d_col_idxs));
    CHECK_CUDA(cudaFree(d_values));
    CHECK_CUDA(cudaFree(d_x));
    CHECK_CUDA(cudaFree(d_output));
    return 0;
}