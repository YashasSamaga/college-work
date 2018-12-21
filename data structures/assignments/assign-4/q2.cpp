#include <iostream>
#include <vector>
#include <algorithm>

//#define DEBUG

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
					auto pr = std::equal_range(rhs.begin(), rhs.end(), key);
					count += pr.second - pr.first;
				}		 
				if (right % 2) {
					const auto& lhs = c[right - 1];
					auto pr = std::equal_range(lhs.begin(), lhs.end(), key);
					count += pr.second - pr.first;
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

using Graph = typename std::vector<std::vector<int>>;
Graph graph;

struct node_property_t { 
	int children, preorder_pos; 
};
std::vector<node_property_t> node_property;
std::vector<int> preorder_depth;
void dfs(int parent, int current, int cur_depth) {
	node_property[current].preorder_pos = preorder_depth.size();
	preorder_depth.push_back(cur_depth + 1);
	for(auto i : graph[current]) {
		if(parent != i) {
			dfs(current, i, cur_depth + 1);
			node_property[current].children += node_property[i].children;
		}
	}
}

int main () {
	int N, Q;
	std::cin >> N >> Q;
	
	graph.resize(N);
	for(int i = 0; i < N - 1; i++) {
		int from, to;
		std::cin >> from >> to;
		graph[from - 1].push_back(to - 1);
		graph[to - 1].push_back(from - 1);
	}

	node_property.resize(N, { 1, 0 });
	dfs(0, 0, 0);
	
	MergeSortTree mstree(std::move(preorder_depth));

	#ifdef DEBUG
	for(const auto &i : node_property)
		std::cout << i.children << ' ';
	std::cout << '\n';
	
	for(const auto &i : node_property)
		std::cout << i.preorder_pos << ' ';
	std::cout << '\n';
	
	for(auto i : preorder_depth)
		std::cout << i << ' ';
	std::cout << '\n';
	#endif
	
	for(int i = 0; i < Q; i++) {
		int v, d;
		std::cin >> v >> d;		
		const auto& property = node_property[v - 1];
		int ppos = property.preorder_pos;
		std::cout << mstree.query(ppos, ppos + property.children, preorder_depth[ppos] + d) << '\n';
	}
	return 0;
}
