#include <iostream>
#include <set>
#include <vector>
#include <limits>
#include <algorithm>
#include <utility>
#include <cstdint>

struct Edge {
	Edge(int target, int64_t weight) : target(target), weight(weight) { }
	int target;
	int64_t weight;	
};

using Graph = typename std::vector<std::vector<Edge>>;

template <class UnaryFunction>
void shortest_path(const Graph& graph, int start, std::vector<int64_t>& distance, UnaryFunction func) {
	constexpr int64_t max = std::numeric_limits<int64_t>::max();
	distance.resize(graph.size(), max);
	
	std::set<std::pair<int64_t, int>> unfinished; //distance, node
	unfinished.emplace(0, start);
	distance[start] = 0;
	
	while(!unfinished.empty()) {
		auto itr = unfinished.begin();
		int64_t dist = itr->first;
		int	index = itr->second;		
		unfinished.erase(itr);
		
		for(const auto& edge : graph[index]) {
			if(func(edge.weight)) {
				int target = edge.target;
				if(distance[target] > dist + edge.weight) {
					if(distance[target] != max)
						unfinished.erase(std::make_pair(distance[target], target));
					distance[target] = dist + edge.weight;
					unfinished.emplace(distance[target], target);
				}
			}
		}
	}
}

int main () {
	int N, M;
	std::cin >> N >> M;
	
	int S, T;
	std::cin >> S >> T;
	S--;
	T--;
	
	Graph graph(N);
	for(int i = 0; i < M; i++) {
		int from, to, E;
		std::cin >> from >> to >> E;
		
		graph[from - 1].emplace_back(to - 1, E); /* E promoted to int64_t */
		graph[to - 1].emplace_back(from - 1, E);	
	}
	
	int64_t A, B;
	std::cin >> A >> B;
	
	std::vector<int64_t> distance_tr1;
	shortest_path(graph, S, distance_tr1, [A](int64_t weight) { return weight <= A; });
	
	std::vector<int64_t> distance_tr2;
	shortest_path(graph, T, distance_tr2, [B](int64_t weight) { return weight >= B; });
	
	constexpr int64_t max = std::numeric_limits<int64_t>::max();
	int64_t min = max;
	for(int i = 0; i < N; i++)
		if(distance_tr1[i] != max && distance_tr2[i] != max)
			min = std::min(min, distance_tr1[i] + distance_tr2[i]);

	if(min == max)
		std::cout << -1;
	else
		std::cout << min;
	return 0;
}
