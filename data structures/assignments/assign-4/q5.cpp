#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using Graph = typename std::vector<std::vector<int>>;

Graph graph;
std::vector<int> states;
std::vector<int> data;

void dfs(int parent, int current) {
	int count = states[current];
	for(auto i : graph[current]) {
		if(i != parent) {
			dfs(current, i);
			if(data[i] > 0)
				count += data[i];
		}
	}
	data[current] = count;	
}

int main () {
	int N;
	std::cin >> N;

	graph.resize(N);
	states.resize(N);
	data.resize(N, 0);
	
	for(int i = 0; i < N; i++) {
		int owner;
		std::cin >> owner;
		states[i] = owner == 0 ? 1 : -1;
	}
	
	for(int i = 0; i < N - 1; i++) {
		int from, to, owner;
		std::cin >> from >> to;		
		graph[from - 1].push_back(to - 1);
		graph[to - 1].push_back(from - 1);
	}	
	
	dfs(0, 0);
	int for_petya = *std::max_element(data.begin(), data.end());
	
	std::transform(states.begin(), states.end(), states.begin(), std::negate<int>());
	dfs(0, 0);
	int for_vasya = *std::max_element(data.begin(), data.end());
	
	std::cout << std::max(for_petya, for_vasya);
	return 0;
}
