#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>

using Graph = typename std::vector<std::vector<int>>;

int LISLength(const std::vector<int>& series) {
	if(series.size() == 0)
		return 0;

	std::vector<int> tail;
	tail.push_back(series[0]);

	for(int i = 1; i < series.size(); i++) {
		int item = series[i];
		if(item < tail[0]) {
			tail[0] = item;
		} else if(item > tail.back()) {
			tail.push_back(item);
		} else {
			auto itr = std::upper_bound(tail.begin(), tail.end(), item);
			if(itr != tail.end() && *(itr - 1) != item)
			 	*itr = item;			
		}
	}
	return tail.size();
}

std::vector<int> data;

int length = 0;
std::vector<int> sequence;
void dfs(const Graph& graph, int parent, int node) {
	//std::cout << "DFS: " << parent << " " << node << '\n';
	sequence.push_back(data[node]);
	if(graph[node].size() == 1 && node != 0) {
		//std::cout << "LIS\n";
		length = std::max(length, LISLength(sequence));
	} else {		
		for(auto i : graph[node]) {
			//std::cout << "call check: " << i << " " << parent << '\n';
			if(i != parent)
				dfs(graph, node, i);
		}
	}
	sequence.pop_back();
}

int main () {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	int N;
	std::cin >> N;

	//std::cout << LISLength({1, 5, 3, 7, 7, 9, 7, 8});
	//return 0;

	Graph graph(N);
	for(int i = 0; i < N - 1; i++) {
		int from, to;
		std::cin >> from >> to;
		graph[from - 1].push_back(to - 1);
		graph[to - 1].push_back(from - 1);
	}

	data.resize(N);
	for(int i = 0; i < N; i++) {
		std::cin >> data[i];
	}
	
	if(N == 1)
		return std::cout << 1, 0;

	dfs(graph, 0, 0);
	std::cout << length;		
	return 0;
}
