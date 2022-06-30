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
    void sort(const T* RESTRICT input, T* RESTRICT output, int N)
    {
        std::copy(input, input + N, output);
        std::sort(output, output + N);
    }

    template <class T>
    void radix_sort(const T* RESTRICT input, T* RESTRICT output, int N)
    {
        std::copy(input, input + N, output);

        constexpr int NUM_ELEMENTS_PER_SEGMENT = 16;
        constexpr int BITS_PER_ITERATION = 4;
        for (int starting_bit = 0; starting_bit < sizeof(T) * 8; starting_bit += BITS_PER_ITERATION)
        {
            bool masks[NUM_ELEMENTS_PER_SEGMENT];
            int pos[NUM_ELEMENTS_PER_SEGMENT + 1];
            T sorted_nums[NUM_ELEMENTS_PER_SEGMENT];

            for (int pattern = (1 << (BITS_PER_ITERATION - 1)) - 1; pattern >= 0; pattern--)
            {
                for (int i = 0; i < NUM_ELEMENTS_PER_SEGMENT; i++)
                {
                    auto value = output[i];
                    auto bits = (value >> starting_bit) & ((1 << (BITS_PER_ITERATION - 1)) - 1);
                    masks[i] = (bits == pattern);
                }

                pos[0] = 0;
                for (int i = 1; i < NUM_ELEMENTS_PER_SEGMENT; i++)
                    pos[i] = pos[i - 1] + masks[i - 1];

                auto total_matches = pos[NUM_ELEMENTS_PER_SEGMENT - 1] + masks[NUM_ELEMENTS_PER_SEGMENT - 1];

                for (int i = 0; i < NUM_ELEMENTS_PER_SEGMENT; i++)
                {
                    if (masks[i])
                        sorted_nums[pos[i]] = output[i];
                }

                // invert masks
                for (int i = 0; i < NUM_ELEMENTS_PER_SEGMENT; i++)
                    masks[i] = !masks[i];
                
                pos[0] = total_matches;
                for (int i = 1; i <= NUM_ELEMENTS_PER_SEGMENT; i++)
                    pos[i] = pos[i - 1] + masks[i - 1];
  
                for (int i = 0; i < NUM_ELEMENTS_PER_SEGMENT; i++)
                {
                    if (masks[i])
                        sorted_nums[pos[i]] = output[i];
                }

                std::cout << "PASS1\n";
                print_range(sorted_nums, sorted_nums + NUM_ELEMENTS_PER_SEGMENT);
                std::cout << '\n';
                std::copy(sorted_nums, sorted_nums + NUM_ELEMENTS_PER_SEGMENT, output);
            }
        }
    }
}

namespace thrust_gpu {
    template <class T>
    void sort(const T* input, T* output, int N)
    {
        thrust::copy(thrust::device, input, input + N, output);
        thrust::sort(thrust::device, output, output + N);
    }
}

namespace gpu {

}

int main ()
{
    using T = int;
    const int N = 16;    

    constexpr float THRESHOLD = 0.001;
    
    std::vector<T> input(N);
    random_fill_integers(std::begin(input), std::end(input));

    T* d_input, *d_output;
    CHECK_CUDA(cudaMalloc(&d_input, input.size() * sizeof(T)));
    CHECK_CUDA(cudaMalloc(&d_output, input.size() * sizeof(T)));

    std::vector<T> output_cpu(N);
    auto cpu_time = benchmark([&input, &output_cpu, N] {
        cpu::radix_sort(input.data(), output_cpu.data(), N);
    });
    std::cout << "[CPU] Running time: " << to_milliseconds(cpu_time).count() << "ms\n";
    std::cout << std::endl;
print_range(std::begin(output_cpu), std::end(output_cpu));

    std::vector<T> output_thrust(N);
    auto thrust_gpu_time = benchmark([&] {
        CHECK_CUDA(cudaMemcpy(d_input, input.data(), input.size() * sizeof(T), cudaMemcpyHostToDevice));
        thrust_gpu::sort(d_input, d_output, N);
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
        // gpu::inclusive_scan_v2(d_input, d_output, N);
        CHECK_CUDA(cudaMemcpy(output_gpu.data(), d_output, output_gpu.size() * sizeof(T), cudaMemcpyDeviceToHost));
    });
    std::cout << "[GPU] Running time (incl. memory copy): " << to_milliseconds(gpu_time).count() << "ms" << std::endl;
    print_result(std::begin(output_cpu), std::end(output_cpu), std::begin(output_gpu), THRESHOLD);

    CHECK_CUDA(cudaFree(d_input));
    CHECK_CUDA(cudaFree(d_output));
    return 0;
}