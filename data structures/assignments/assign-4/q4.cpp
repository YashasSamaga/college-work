#include <iostream>
#include <functional>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <initializer_list>
#include <cassert>

class MergeSortTree {
	public:
		typedef	int size_type;
	
		explicit MergeSortTree(std::vector<int>&& cont) {
			c.resize(2*cont.size());
			for(int i = 0; i < cont.size(); i++) {
				auto& v = c[cont.size() + i];
				v.push_back(cont[i]);
			}
			build();
		}
		
		int query(size_type left, size_type right, int key) const {
			int count = 0;
			for (left += c.size()/2, right += c.size()/2; left < right; left /= 2, right /= 2) {
				if (left % 2) {
					const auto& rhs = c[left++];
					count += std::upper_bound(rhs.begin(), rhs.end(), key) - rhs.begin();
				}		 
				if (right % 2) {
					const auto& lhs = c[right - 1];
					count += std::upper_bound(lhs.begin(), lhs.end(), key) - lhs.begin();
				}
			}
			return count;
		}	
				
	protected:
		void build() {
			for(int i = c.size()/2 - 1; i > 0; i--) {
				const auto& lhs = c[i*2], rhs = c[i*2 + 1];
				std::vector<int> result(lhs.size() + rhs.size());
				std::merge(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), result.begin());
				c[i] = std::move(result);
			}
		}
		
		std::vector<std::vector<int>> c;
};

int main () {
	int N;
	std::cin >> N;
	
	std::vector<int> data(N);
	for(int i = 0; i < N; i++)
		std::cin >> data[i];
	
	MergeSortTree mstree(std::move(data));
	
	int Q;
	std::cin >> Q;
	for(int i = 0; i < Q; i++) {
		int left, right, key;
		std::cin >> left >> right >> key;
		std::cout << mstree.query(left - 1, right, key) << '\n';
	}
	return 0;
}
