#include <iostream>
#include <functional>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <initializer_list>
#include <cassert>

template <typename T, std::size_t N>
class SquareMatrix {
	public:
		SquareMatrix() {
			std::fill_n(&data[0][0], N * N, 0);
			for(int i = 0; i < N; i++)
				data[i][i] = 1;
		};
		
		SquareMatrix(std::initializer_list<T> init) {
			assert(init.size() == N * N);
			std::copy_n(init.begin(), N*N, &data[0][0]);
		}
		
		SquareMatrix operator*(const SquareMatrix& rhs) const {
			const int64_t MOD = 1000000000 + 7;
			SquareMatrix tmp;
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < N; j++) {
					tmp.data[i][j] = 0;
					for(int k = 0; k < N; k++) {
						tmp.data[i][j] = (tmp.data[i][j] + (this->data[i][k] * rhs.data[k][j])%MOD) % MOD;
					}					
				}
			}
			return tmp;
		}
	
		T data[N][N];
};

template <typename T, class Container = std::vector<T>, class BinaryOperation = std::plus<T>>
class SegmentTree {
	public:
		typedef	typename Container::size_type size_type;
	
		explicit SegmentTree(Container&& cont) {
			c.resize(2*cont.size());
			std::move_backward(cont.begin(), cont.end(), c.end());
			build();
		}

		void update(size_type idx, T value) {
			idx += c.size()/2;
			c[idx] = value;
			while(idx > 1) {
				if(idx % 2 == 0)
					c[idx/2] = op(c[idx], c[idx + 1]);
				else
					c[idx/2] = op(c[idx - 1], c[idx]);			
				idx /= 2;
			}	
		}

		T query(size_type left, size_type right) const {
			T result_left = T();
			T result_right = T();
			for (left += c.size()/2, right += c.size()/2; left < right; left /= 2, right /= 2) {
				if (left % 2 == 1)
					result_left = op(result_left, c[left++]);			 
				if (right % 2 == 1)
					result_right = op(c[--right], result_right);
			}	 
			return op(result_left, result_right);
		}
				
	protected:
		void build() {
			for(int i = c.size()/2 - 1; i > 0; i--)
				c[i] = op(c[i*2], c[i*2 + 1]);
		}
		
		Container c;
		BinaryOperation op;
};

using Matrix = SquareMatrix<int64_t, 2>;

int main () {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int N;
	std::cin >> N;
	
	std::vector<Matrix> matrices(N);
	for(int i = 0; i < N; i++) {
		auto& m = matrices[i];
		std::cin >> m.data[0][0] >> m.data[0][1] >> m.data[1][0] >> m.data[1][1];		
	}
	
	SegmentTree<Matrix, std::vector<Matrix>, std::multiplies<Matrix>> segtree(std::move(matrices));
	
	int Q;
	std::cin >> Q;
	
	while(Q--) {
		int type;
		std::cin >> type;
		switch(type) {
			case 1:
			{
				int left, right;
				std::cin >> left >> right;
				Matrix matrix = segtree.query(left - 1, right);
				std::cout << matrix.data[0][0] << ' ' << matrix.data[0][1] << ' ' << matrix.data[1][0] << ' ' << matrix.data[1][1] << '\n';		
				break;
			}
			case 2:
			{
				int index, a11, a12, a21, a22;
				std::cin >> index;
				std::cin >> a11 >> a12 >> a21 >> a22;		
				segtree.update(index - 1, Matrix({a11, a12, a21, a22}));
				break;
			}		
		}
	}
	return 0;
}

