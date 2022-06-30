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

/************************** CONVOLUTION IMPLEMENTATIONS BEGIN **********************/

namespace cpu_impl {
    template <class T>
    void convolve3d(const T* RESTRICT input, int N, const T* RESTRICT filter, int M, T* RESTRICT output)
    {
        auto K = N - M + 1;
        auto compute_idx = [](auto z, auto y, auto x, int dim) {
            return (z * dim + y) * dim + x;
        };

        for (int start_input_x = 0; start_input_x < N - M + 1; start_input_x++)
        {
            for (int start_input_y = 0; start_input_y < N - M + 1; start_input_y++)
            {
                for (int start_input_z = 0; start_input_z < N - M + 1; start_input_z++)
                {
                    T accumulator = 0;
                    for (int x = 0; x < M; x++)
                    {
                        for (int y = 0; y < M; y++)
                        {
                            for (int z = 0; z < M; z++)
                            {
                                auto w_idx = compute_idx(z, y, x, M);
                                auto i_idx = compute_idx(start_input_z + z, start_input_y + y, start_input_x + x, N);
                                accumulator += filter[w_idx] * input[i_idx];
                            }
                        }
                    }
                    auto out_idx = compute_idx(start_input_z, start_input_y, start_input_x, K);
                    output [out_idx] = accumulator;
                }
            }
        }
    }
}

namespace gpu_impl {

    template <class T> __device__ T mul_ftz(T x, T y) { return x * y; }
    template <> inline __device__ float mul_ftz(float x, float y) {
        float result;
        asm("mul.ftz.f32 %0, %1, %2;" : "=f"(result) : "f"(x), "f"(y));
        return result;
    }

    template <> inline __device__ double mul_ftz(double x, double y) {
        double result;
        asm("mul.ftz.f64 %0, %1, %2;" : "=d"(result) : "d"(x), "d"(y));
        return result;
    }

    template <class T>
    __global__
    void convolve3d(const T* CUDA_RESTRICT input, int N, const T* CUDA_RESTRICT filter, int M, T* CUDA_RESTRICT output)
    {
        auto K = N - M + 1;
        auto compute_idx = [](auto z, auto y, auto x, int dim) {
            return (z * dim + y) * dim + x;
        };

        for (int out_idx = threadIdx.x + blockIdx.x * blockDim.x; out_idx < K * K * K; out_idx += gridDim.x * blockDim.x)
        {
            auto start_input_x = out_idx % K;
            auto start_input_y = (out_idx / K) % K;
            auto start_input_z = out_idx / (K * K);

            T accumulator = 0;
            for (int x = 0; x < M; x++)
            {
                for (int y = 0; y < M; y++)
                {
                    for (int z = 0; z < M; z++)
                    {
                        auto w_idx = compute_idx(z, y, x, M);
                        auto i_idx = compute_idx(start_input_z + z, start_input_y + y, start_input_x + x, N);
                        accumulator += filter[w_idx] * input[i_idx];
                    }
                }
            }
            output[out_idx] = accumulator;
        }
    }
}

/************************** DOT PRODUCT IMPLEMENTATIONS END **********************/

int main ()
{
    using T = double;
    constexpr int N = 128;
    constexpr int M = 9;

    constexpr int output_dim = N - M + 1;

    constexpr T THRESHOLD = 1e-2;

    std::vector<T> input(N * N * N), weights(M * M * M), output_cpu(output_dim * output_dim * output_dim);
    random_fill(std::begin(input), std::end(input));
    random_fill(std::begin(weights), std::end(weights));

    T* d_input, *d_weights, *d_output;
    CHECK_CUDA(cudaMalloc(&d_input, input.size() * sizeof(T)));
    CHECK_CUDA(cudaMalloc(&d_weights, weights.size() * sizeof(T)));
    CHECK_CUDA(cudaMalloc(&d_output, output_cpu.size() * sizeof(T)));

    std::cout << "CPU Evaluation:\n";
    {
        auto cpu_time = benchmark([&] {
            cpu_impl::convolve3d(input.data(), N, weights.data(), M, output_cpu.data());
        });
        std::cout << "\tRunning time: " << to_milliseconds(cpu_time).count() << "ms\n" << std::endl;
    }
    std::cout << std::endl;

    std::vector<T> output_gpu(output_cpu.size());
    std::cout << "GPU Evaluation:\n";
    {
        auto cpu_time = benchmark([&] {
            CHECK_CUDA(cudaMemcpy(d_input, input.data(), input.size() * sizeof(T), cudaMemcpyHostToDevice));
            CHECK_CUDA(cudaMemcpy(d_weights, weights.data(), weights.size() * sizeof(T), cudaMemcpyHostToDevice));

            int grid_size = 0, block_size = 0;
            CHECK_CUDA(cudaOccupancyMaxPotentialBlockSize(&grid_size, &block_size, gpu_impl::convolve3d<T>, 0));
            gpu_impl::convolve3d<<<grid_size, block_size>>>(d_input, N, d_weights, M, d_output);

            CHECK_CUDA(cudaMemcpy(output_gpu.data(), d_output, output_gpu.size() * sizeof(T), cudaMemcpyDeviceToHost));
        });
        std::cout << "\tRunning time (incl. memory copy): " << to_milliseconds(cpu_time).count() << "ms\n" << std::endl;
        print_result(std::begin(output_cpu), std::end(output_cpu), std::begin(output_gpu), THRESHOLD);
    }

    CHECK_CUDA(cudaFree(d_input));
    CHECK_CUDA(cudaFree(d_weights));
    CHECK_CUDA(cudaFree(d_output));
    return 0;
}
