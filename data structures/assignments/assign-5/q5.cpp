#include <iostream>
#include <vector>
#include <limits>
#include <set>
#include <cassert>

template <typename T>
class ordered_pair {
	public:
		ordered_pair() : first(max), second(max) { }
		ordered_pair(T u) : first(u), second(max) { }
		ordered_pair(T u, T v) {
			first = u < v ? u : v;
			second = u < v ? v : u;
		}
		
		void try_insert(T value) {
			if(value >= second)
				return;
				
			if(value >= first)
				second = value;
				
			if(value < first) {
				second = first;
				first = value;
			}
		}
		
		T first;
		T second;
	
	private:
		static constexpr T max = std::numeric_limits<T>::max();
};

struct Edge {
	Edge(int target, int64_t weight) : target(target), weight(weight) { }
	int target;
	int64_t weight;
};

using Graph = typename std::vector<std::vector<Edge>>;

int shortest_path(const Graph& graph, std::set<std::pair<int64_t, int>>& start, int dest) {
	constexpr int64_t max = std::numeric_limits<int64_t>::max();

	std::vector<ordered_pair<int64_t>> distance(graph.size());
	for(const auto& pr : start) {
		distance[pr.second].first = 
		distance[pr.second].second = 0;
	}
	
	auto& unfinished = start; //second distance, node	
	while(!unfinished.empty()) {
		auto itr = unfinished.begin();
		int	index = itr->second;	
		unfinished.erase(itr);
			
		for(const auto& edge : graph[index]) {
			int target = edge.target;
			if(distance[target].second > distance[index].second + edge.weight) {
				if(distance[target].first == max) {
					distance[target].try_insert(distance[index].second + edge.weight);
				} else if(distance[target].second == max) {
					distance[target].try_insert(distance[index].second + edge.weight);
					unfinished.emplace(distance[target].second, target);
					assert(distance[target].second != max);
				} else {
					unfinished.erase(unfinished.find(std::make_pair(distance[target].second, target)));					
					distance[target].try_insert(distance[index].second + edge.weight);					
					unfinished.emplace(distance[target].second, target);
				}
			}
		}		
	}
	return distance[dest].second;
}

int main () {
	int N, M, K;
	std::cin >> N >> M >> K;
	
	Graph graph(N);
	for(int i = 0; i < M; i++) {
		int from, to, weight;
		std::cin >> from >> to >> weight;
		graph[from].emplace_back(to, weight);
		graph[to].emplace_back(from, weight);
	}
	
	std::set<std::pair<int64_t, int>> start;
	for(int i = 0; i < K; i++) {
		int node;
		std::cin >> node;
		start.emplace(0, node);
	}
	
	int64_t len = shortest_path(graph, start, 0);
	if(len == std::numeric_limits<int64_t>::max())
		len = -1;
		
	std::cout << len;
	return 0;
}
