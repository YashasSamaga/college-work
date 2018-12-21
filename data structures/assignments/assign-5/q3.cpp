#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

template <typename T, class Container = std::vector<T>, class BinaryOperation = std::plus<T>>
class SegmentTree {
	static 	constexpr int64_t MOD = 1000000000 + 7;
	
	public:
		typedef	typename Container::size_type size_type;
	
		explicit SegmentTree(Container&& cont) {
			c.resize(2*cont.size());
			std::move_backward(cont.begin(), cont.end(), c.end());
			build();
		}

		void update(size_type idx, T value) {
			idx += c.size()/2;
			c[idx] = value % MOD;
			while(idx > 1) {
				if(idx % 2 == 0)
					c[idx/2] = op(c[idx], c[idx + 1]) % MOD;
				else
					c[idx/2] = op(c[idx - 1], c[idx]) % MOD;			
				idx /= 2;
			}	
		}

		T query(size_type left, size_type right) const {
			T result_left = T();
			T result_right = T();
			for (left += c.size()/2, right += c.size()/2; left < right; left /= 2, right /= 2) {
				if (left % 2)
					result_left = op(result_left, c[left++]) % MOD;
				if (right % 2)
					result_right = op(c[--right], result_right) % MOD;
			}	 
			return op(result_left, result_right) % MOD;
		}
				
	protected:
		void build() {
			for(int i = c.size()/2 - 1; i > 0; i--)
				c[i] = op(c[i*2], c[i*2 + 1]) % MOD;
		}
		
		Container c;
		BinaryOperation op;
};

template <typename T>
int64_t LengthLIS(const std::vector<T>& series) {
	if(series.size() == 0)
		return 0; 

	const int size = 1000000 + 1;
	SegmentTree<int64_t> count(std::move(std::vector<int64_t>(size, 0)));
	
	for(int i = 0; i < series.size(); i++) {
		int64_t item = series[i];
		count.update(item, count.query(0, item + 1) * item + item);
	}	
	return count.query(0, size);
}

int main () {
	int T;
	std::cin >> T;
	
	while(T--) {
		int32_t N;
		std::cin >> N;
		
		std::vector<int32_t> nums(N);
		for(int i = 0; i < N; i++)
			std::cin >> nums[i];
			
		std::cout << LengthLIS(nums) << '\n';
	}
	return 0;
}
