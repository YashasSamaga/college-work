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
#include <cublas_v2.h>

#include <thrust/inner_product.h>
#include <thrust/execution_policy.h>

#include "../helpers.hpp"

/************************** DOT PRODUCT IMPLEMENTATIONS BEGIN **********************/

namespace cpu_impl {
    template <class T>
    void dotproduct(const T* RESTRICT x, const T* RESTRICT y, T* RESTRICT output, int N)
    {
        T sum{0};
        for (int i = 0; i < N; i++)
            sum += x[i] * y[i];
        *output = sum;
    }

    template <class T>
    void dotproduct_stl(const T* RESTRICT x, const T* RESTRICT y, T* RESTRICT output, int N)
    {
        *output = std::inner_product(x, x + N, y, T{0});
    }
}

namespace cublas_impl {
    template <class T>
    void dotproduct(cublasHandle_t handle, const T* CUDA_RESTRICT x, const T* CUDA_RESTRICT y, T* CUDA_RESTRICT output, int N)
    {
        static_assert(std::is_same<T, float>::value || std::is_same<T, double>::value);
        if constexpr (std::is_same<T, float>::value)
        {
            CHECK_CUBLAS(cublasSdot(
                handle, N,
                x, 1,
                y, 1,
                output)
            );
        }
        else if constexpr (std::is_same<T, double>::value)
        {
            CHECK_CUBLAS(cublasDdot(
                handle, N,
                x, 1,
                y, 1,
                output)
            );
        }
    }
}

namespace thrust_impl {
    template <class T>
    void dotproduct(const T* CUDA_RESTRICT x, const T* CUDA_RESTRICT y, T* CUDA_RESTRICT output, int N)
    {
        *output = thrust::inner_product(thrust::device, x, x + N, y, T{0});
    }
}

namespace gpu_impl {
    template <class T>
    __global__
    void fill(T* x, T value, int N)
    {
        for (int i = threadIdx.x + blockIdx.x * blockDim.x; i < N; i += blockDim.x * gridDim.x)
            x[i] = value;
    }

    template <class T>
    __global__
    void dotproduct_v1(const T* CUDA_RESTRICT x, const T* CUDA_RESTRICT y, T* CUDA_RESTRICT output, int N)
    {
        for (int i = threadIdx.x + blockIdx.x * blockDim.x; i < N; i += blockDim.x * gridDim.x)
            atomicAdd(output, x[i] * y[i]);
    }

    template <class T>
    __global__
    void dotproduct_v2(const T* CUDA_RESTRICT x, const T* CUDA_RESTRICT y, T* CUDA_RESTRICT output, int N)
    {
        T local_sum(0);
        for (int i = threadIdx.x + blockIdx.x * blockDim.x; i < N; i += blockDim.x * gridDim.x)
            local_sum += x[i] * y[i];
        atomicAdd(output, local_sum);
    }

    template <class T>
    __global__
    void dotproduct_v3(const T* CUDA_RESTRICT x, const T* CUDA_RESTRICT y, T* CUDA_RESTRICT output, int N)
    {
        T local_sum(0);
        for (int i = threadIdx.x + blockIdx.x * blockDim.x; i < N; i += blockDim.x * gridDim.x)
            local_sum += x[i] * y[i];
        auto warpSum = warpReduceSum(local_sum);
        if (threadIdx.x % 32 == 0)
            atomicAdd(output, local_sum);
    }
}

/************************** DOT PRODUCT IMPLEMENTATIONS END **********************/

int main ()
{
    using T = double;
    constexpr int N = 100'000'000;

    constexpr T THRESHOLD = 1e-1;

    std::vector<T> x(N), y(N);
    random_fill(std::begin(x), std::end(x));
    random_fill(std::begin(y), std::end(y));

    T* d_x, *d_y, *d_output;
    CHECK_CUDA(cudaMalloc(&d_x, x.size() * sizeof(T)));
    CHECK_CUDA(cudaMalloc(&d_y, y.size() * sizeof(T)));
    CHECK_CUDA(cudaMalloc(&d_output, sizeof(T)));

    cublasHandle_t cublas_handle;
    CHECK_CUBLAS(cublasCreate(&cublas_handle));

    T output_cpu;
    std::cout << "CPU Evaluation:\n";
    {
        auto cpu_time = benchmark([&] {
            cpu_impl::dotproduct(x.data(), y.data(), &output_cpu, N);
        });
        std::cout << "\tRunning time: " << to_milliseconds(cpu_time).count() << "ms\n";
    }
    std::cout << std::endl;

    std::cout << "GPU Memory Transfer Evaluation:\n";
    {
        auto h2d_transfer_time = benchmark([&] {
            CHECK_CUDA(cudaMemcpy(d_x, x.data(), x.size() * sizeof(T), cudaMemcpyHostToDevice));
            CHECK_CUDA(cudaMemcpy(d_y, y.data(), y.size() * sizeof(T), cudaMemcpyHostToDevice));
        });
        std::cout << "[H2D] Transfer time: " << to_milliseconds(h2d_transfer_time).count() << "ms" << '\n';

        T dummy;
        auto d2h_transfer_time = benchmark([&] {
            CHECK_CUDA(cudaMemcpy(&dummy, d_output, sizeof(T), cudaMemcpyDeviceToHost));
        });
        std::cout << "[D2H] Transfer time: " << to_milliseconds(d2h_transfer_time).count() << "ms" << '\n';
    }
    std::cout << std::endl;

    T cublas_output_gpu;
    std::cout << "cuBLAS Evaluation:\n";
    {
        CHECK_CUDA(cudaMemcpy(d_x, x.data(), x.size() * sizeof(T), cudaMemcpyHostToDevice));
        CHECK_CUDA(cudaMemcpy(d_y, y.data(), y.size() * sizeof(T), cudaMemcpyHostToDevice));
        auto cublas_gpu_time = benchmark([&] {
            cublas_impl::dotproduct(cublas_handle, d_x, d_y, d_output, N);
            CHECK_CUDA(cudaGetLastError());
            CHECK_CUDA(cudaDeviceSynchronize());
        });
        CHECK_CUDA(cudaMemcpy(&cublas_output_gpu, d_output, sizeof(T), cudaMemcpyDeviceToHost));
        std::cout << "\tKernel Time: " << to_milliseconds(cublas_gpu_time).count() << "ms\n";

        auto error = std::abs(output_cpu - cublas_output_gpu);
        std::cout << "\tOUTPUT >> cpu: " << output_cpu << ", gpu: " << cublas_output_gpu << '\n';
        std::cout << "\tDIFF >> " << error << '\n';
        std::cout << "\tACCURACY TEST: " << error << "; " << (error < THRESHOLD ? "PASSED" : "FAILED") << '\n';
    }
    std::cout << std::endl;

    T output_gpu = 0;
    std::cout << "Custom GPU Implementation Evaluation:\n";
    {
        CHECK_CUDA(cudaMemcpy(d_x, x.data(), x.size() * sizeof(T), cudaMemcpyHostToDevice));
        CHECK_CUDA(cudaMemcpy(d_y, y.data(), y.size() * sizeof(T), cudaMemcpyHostToDevice));
        auto gpu_time = benchmark([&] {
            gpu_impl::fill<<<1, 1>>>(d_output, T(0), 1);
            CHECK_CUDA(cudaGetLastError());

            int grid_size = 0, block_size = 0;
            CHECK_CUDA(cudaOccupancyMaxPotentialBlockSize(&grid_size, &block_size, gpu_impl::dotproduct_v2<T>, 0));
            gpu_impl::dotproduct_v2<<<grid_size, block_size>>>(d_x, d_y, d_output, N);
            CHECK_CUDA(cudaGetLastError());
            
            CHECK_CUDA(cudaDeviceSynchronize());
        });
        CHECK_CUDA(cudaMemcpy(&output_gpu, d_output, sizeof(T), cudaMemcpyDeviceToHost));
        std::cout << "\t[GPU] Kernel Time: " << to_milliseconds(gpu_time).count() << "ms\n";

        auto error = std::abs(output_cpu - output_gpu);
        std::cout << "\tOUTPUT >> cpu: " << output_cpu << ", gpu: " << output_gpu << '\n';
        std::cout << "\tDIFF >> " << error << '\n';
        std::cout << "\tACCURACY TEST: " << error << "; " << (error < THRESHOLD ? "PASSED" : "FAILED") << '\n';
    }

    CHECK_CUBLAS(cublasDestroy(cublas_handle));
    CHECK_CUDA(cudaFree(d_x));
    CHECK_CUDA(cudaFree(d_y));
    CHECK_CUDA(cudaFree(d_output));
    return 0;
}