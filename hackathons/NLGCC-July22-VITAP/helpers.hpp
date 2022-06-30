#include <cuda_runtime.h>
#include <cublas_v2.h>

#if defined(__GNUC__) && ((__GNUC__ > 3) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
#   define RESTRICT __restrict
#elif defined(_MSC_VER) && _MSC_VER >= 1400
#   define RESTRICT __restrict
#else
#   define RESTRICT
#endif

#define CUDA_RESTRICT __restrict__

#define CHECK_CUDA(expr) detail::check_cuda_status((expr), __FILE__, __LINE__)  

namespace detail {
    class exception : public std::exception {
    public:
        explicit exception(std::string msg) : what_msg(std::move(msg)) { }
        virtual ~exception() { }

        const char* what() const noexcept override { return what_msg.c_str(); }

    protected:
        std::string what_msg;
    };

    void check_cuda_status(cudaError_t error, std::string filename, std::size_t lineno) {
        if (error != cudaSuccess) {
            std::ostringstream stream;
            stream << "CUDA Error: " << filename << ":" << lineno << '\n';
            stream << cudaGetErrorString(error) << '\n';
            throw exception(stream.str());
        }
    }
}

#define CHECK_CUBLAS(expr) detail::check_cublas_status((expr), __FILE__, __LINE__) 

namespace detail {
    void check_cublas_status(cublasStatus_t error, std::string filename, std::size_t lineno) {
        auto cublasGetErrorString = [](cublasStatus_t err) {
            switch (err) {
            case CUBLAS_STATUS_SUCCESS: return "CUBLAS_STATUS_SUCCESS";
            case CUBLAS_STATUS_NOT_INITIALIZED: return "CUBLAS_STATUS_NOT_INITIALIZED";
            case CUBLAS_STATUS_ALLOC_FAILED: return "CUBLAS_STATUS_ALLOC_FAILED";
            case CUBLAS_STATUS_INVALID_VALUE: return "CUBLAS_STATUS_INVALID_VALUE";
            case CUBLAS_STATUS_ARCH_MISMATCH: return "CUBLAS_STATUS_ARCH_MISMATCH";
            case CUBLAS_STATUS_MAPPING_ERROR: return "CUBLAS_STATUS_MAPPING_ERROR";
            case CUBLAS_STATUS_EXECUTION_FAILED: return "CUBLAS_STATUS_EXECUTION_FAILED";
            case CUBLAS_STATUS_INTERNAL_ERROR: return "CUBLAS_STATUS_INTERNAL_ERROR";
            }
            return "UNKNOWN_CUBLAS_ERROR";
        };

        if (error != CUBLAS_STATUS_SUCCESS) {
            std::ostringstream stream;
            stream << "CUBLAS Error: " << filename << ":" << lineno << '\n';
            stream << cublasGetErrorString(error) << '\n';
            throw detail::exception(stream.str());
        }
    }
}

template <class Function, typename ...Args>
auto benchmark(Function function, Args&& ...args) {
    using std::chrono::steady_clock;
    auto start = steady_clock::now();

    function(std::forward<Args>(args)...);
    
    auto end = steady_clock::now();
    return end - start;
}

template <class T>
auto to_milliseconds(const T& duration) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration);
}

template <class ForwardItr>
void random_fill(ForwardItr first, ForwardItr last)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-1, 1);
    std::generate(first, last, [&]{ return dist(gen); }); 
}

template <class ForwardItr>
void random_fill_integers(ForwardItr first, ForwardItr last)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 100);
    std::generate(first, last, [&]{ return dist(gen); }); 
}

template <class ForwardItr1, class ForwardItr2>
auto linf_norm(ForwardItr1 first1, ForwardItr1 last1, ForwardItr2 first2) {
    typename std::iterator_traits<ForwardItr1>::value_type max = 0;
    while(first1 != last1)
    {
        max = std::max(max, std::abs(*first1 - *first2));
        first1++;
        first2++;
    }
    return max;
}

template <class ForwardItr1, class ForwardItr2>
auto l1_norm(ForwardItr1 first1, ForwardItr1 last1, ForwardItr2 first2) {
    typename std::iterator_traits<ForwardItr1>::value_type sum = 0;
    auto num_samples = last1 - first1;
    while(first1 != last1)
    {
        sum += std::abs(*first1 - *first2);
        first1++;
        first2++;
    }
    return sum / num_samples;
}

template <class T, class ForwardItr1, class ForwardItr2>
auto check_result(ForwardItr1 first1, ForwardItr1 last1, ForwardItr2 first2, T ratio) {
    return std::mismatch(first1, last1, first2, [ratio](auto lhs, auto rhs) {
        return std::fabs(rhs - lhs) / std::min(rhs, lhs) < ratio;
    });
}

template <class T, class ForwardItr1, class ForwardItr2>
void print_result(ForwardItr1 first1, ForwardItr1 last1, ForwardItr2 first2, T ratio)
{
    auto pr = check_result(first1, last1, first2, ratio);
    auto match = (pr.first == last1);
    std::cout << "ACCURACY TEST (relative error): " << (match ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Linf norm: " << linf_norm(first1, last1, first2) << '\n';
    std::cout << "L1 norm: " << l1_norm(first1, last1, first2) << '\n';
}

template <class ForwardItr>
void print_range(ForwardItr first, ForwardItr last)
{
    if (first == last)
        return;
    std::cout << *first;
    first++;
    while(first != last)
    {
        std::cout << ", " << *first;
        first++;
    }
}

template <class T>
__inline__ __device__
T warpReduceSum(T val) {
    constexpr int WARP_SIZE = 32;

    #pragma unroll
    for (int offset = WARP_SIZE/2; offset > 0; offset /= 2) 
        val += __shfl_down_sync(0xFFFFFFFF, val, offset);
    return val;
}