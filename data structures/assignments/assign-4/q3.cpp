#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>

using Graph = typename std::vector<std::vector<int>>;

template<class T>
class priority_queue : public std::priority_queue<T> {
	public:
		void push_back(T val) {
			this->push(val);
		}
		
		using std::priority_queue<T>::c;
};

Graph graph;
std::vector<priority_queue<int>> graph_for_sorting;
std::vector<bool> visited;

void dfs(int node) {
	visited[node] = true;
	for(auto i : graph[node]) {
		if(visited[i] == false)
			dfs(i);
	}
}

std::stack<int> sorting;
std::vector<bool> currentTree;
std::vector<bool> visited_ts;
bool topological_sort_util(int node) {
	currentTree[node] = true;
	visited_ts[node] = true;
	while(!graph_for_sorting[node].empty()) {
		int i = graph_for_sorting[node].top();
		graph_for_sorting[node].pop();
		if(currentTree[i] == true)
			return true;
		
		if(visited_ts[i] == false)
			if(topological_sort_util(i))
				return true;
	}
	sorting.push(node);
	currentTree[node] = false;
	return false;
}

bool topological_sorting() {
	std::vector<bool> inorder_zero(graph_for_sorting.size(), true);
	for(const auto& list : graph_for_sorting) {
		for(auto edge : list.c)
			inorder_zero[edge] = false;
	}

	std::priority_queue<int> queue;
	for(int i = 0; i < inorder_zero.size(); i++)
		if(visited[i] == true && inorder_zero[i] == true)
			queue.push(i);

	visited_ts.resize(graph_for_sorting.size(), false);
	currentTree.resize(graph_for_sorting.size(), false);
	while(!queue.empty()) {
		int i = queue.top();
		queue.pop();
		if(visited_ts[i] == false) {
			if(topological_sort_util(i))
				return true;
		}
	}

	if(sorting.size() != std::count(visited.begin(), visited.end(), true))
		return true;
	return false;
}

int main () {
	int n, m, k;
	std::cin >> n >> m >> k;
	
	graph.resize(n);
	for(int i = 0; i < m; i++) {
		int from, to;
		std::cin >> from >> to;
		graph[to - 1].push_back(from - 1); //push in reverse order
	}
	
	visited.resize(n);
	std::fill(visited.begin(), visited.end(), false); //IB
	for(int i = 0; i < k; i++) {
		int course;
		std::cin >> course;
		dfs(course - 1);
	}
	
	graph_for_sorting.resize(n);
	for(int i = 0; i < n; i++) {
		if(visited[i] == true) {			
			for(auto j : graph[i]) {
				if(visited[j] == true)
					graph_for_sorting[j].push_back(i); //push in reverse order to undo the initial reverse ordering
			}
		}
	}

	if(topological_sorting())
		std::cout << "GO HOME RAJAS";
	else {
		std::cout << sorting.size() << '\n';
		while(!sorting.empty()) {			
			std::cout << sorting.top() + 1 << ' ';
			sorting.pop();
		}
	}	
	return 0;
}
