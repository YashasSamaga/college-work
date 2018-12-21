#include <iostream>
#include <vector>
#include <cstdint>
#include <utility>
#include <algorithm>
#include <queue>

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
			if(idx >= c.size())
				return;
				
			c[idx] += value;
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
				if (left % 2)
					result_left = op(result_left, c[left++]);			 
				if (right % 2)
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

using Graph = typename std::vector<std::vector<int>>;

struct node_property_t {
	node_property_t() {
		children_even = children_odd = 0;
	}
	bool even;
	int children_even, children_odd;
	int odd_pos, even_pos; 
};

Graph graph;
std::vector<node_property_t> node_property;

int even_size = 0;
int odd_size = 0;
void dfs(int parent, int current, bool even) {
	node_property[current].even = even;
	node_property[current].even_pos = even_size;
	node_property[current].odd_pos = odd_size;
	
	even ? even_size++ : odd_size++;

	for(auto i : graph[current]) {
		if(parent != i) {
			dfs(current, i, !even);
			node_property[current].children_even += node_property[i].children_odd;
			node_property[current].children_odd += node_property[i].children_even + 1;
		}
	}
}

int main () {
	std::cin.tie(nullptr);

	int N, M;
	std::cin >> N >> M;
	
	std::vector<int64_t> strength(N);
	for(int i = 0; i < N; i++)
		std::cin >> strength[i];
		
	graph.resize(N);
	for(int i = 0; i < N - 1; i++) {
		int from, to;
		std::cin >> from >> to;
		graph[from - 1].push_back(to - 1);
		graph[to - 1].push_back(from - 1);
	}

	node_property.resize(N);
	dfs(0, 0, true);
	
	SegmentTree<int64_t> even_update(std::vector<int64_t>(even_size, 0));
	SegmentTree<int64_t> odd_update(std::vector<int64_t>(odd_size, 0));
	
	for(int i = 0; i < M; i++) {
		int type;
		std::cin >> type;
		switch(type) {
			case 1: {
				int x, v;
				std::cin >> x >> v;
				bool even = node_property[x - 1].even;
				if(even) {
					even_update.update(node_property[x - 1].even_pos, v);
					even_update.update(node_property[x - 1].even_pos + node_property[x - 1].children_even + 1, -v);
					odd_update.update(node_property[x - 1].odd_pos, -v);
					odd_update.update(node_property[x - 1].odd_pos + node_property[x - 1].children_odd, v);
				} else {				
					odd_update.update(node_property[x - 1].odd_pos, v);
					odd_update.update(node_property[x - 1].odd_pos + node_property[x - 1].children_even + 1, -v);
					even_update.update(node_property[x - 1].even_pos, -v);
					even_update.update(node_property[x - 1].even_pos + node_property[x - 1].children_odd, v);
				}
			}
			break;
			case 2: {
				int x;
				std::cin >> x;
				if(node_property[x - 1].even)
					std::cout << strength[x - 1] + even_update.query(0, node_property[x - 1].even_pos + 1) << '\n';
				else
					std::cout << strength[x - 1] + odd_update.query(0, node_property[x - 1].odd_pos + 1) << '\n';
			}
			break;
		}
	}
	return 0;	
}
