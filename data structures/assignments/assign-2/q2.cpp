#include <iostream>
#include <vector>
#include <utility>

struct Node {
	static const int red = 0;
	Node(int n) {
		if (n == red) {
			color = Color::red;
			children.black = 0;
			children.red = 1;
		}
		else {
			color = Color::black;
			children.black = 1;
			children.red = 0;
		}
	};

	enum class Color {
		red,
		black
	} color;

	struct {
		int black;
		int red;
	} children;
};

struct Edge {
	int target;
	std::int64_t weight;
};

using Graph = typename std::vector<std::vector<Edge>>;
template <typename Func>
void dfs_util(Graph& graph, std::vector<bool>& visited, Func f, int parent, int node, std::int64_t weight) {
	if (visited[node] == true)
		return;
	visited[node] = true;

	for (int to = 0; to < graph[node].size(); to++)
		dfs_util(graph, visited, f, node, graph[node][to].target, graph[node][to].weight);
	f(parent, node, weight);
}

template <typename Func>
void dfs(Graph& graph, Func f) {
	std::vector<bool> visited(graph.size(), false);
	dfs_util(graph, visited, f, -1, 0, 0);
}

int main() {
	const int MOD = 1000000000 + 7;	

	int N;
	std::cin >> N;

	int red_nodes = 0, black_nodes = 0;
	std::vector<Node> nodes;
	for (int i = 0; i < N; i++) {
		int n;
		std::cin >> n;
		(n == Node::red) ? red_nodes++ : black_nodes++;
		nodes.emplace_back(n);
	}
	Graph graph(N);
	for (int i = 1; i < N; i++) {
		int a, b;
		std::int64_t w;
		std::cin >> a >> b >> w;
		a--;
		b--;
		graph[a].push_back({b, w%MOD});
		graph[b].push_back({a, w%MOD});
	}

	dfs(graph, [&](int parent, int node, std::int64_t weight) {
		if (parent == -1)
			return;

		Node& cur = nodes[node];
		nodes[parent].children.red += cur.children.red;
		nodes[parent].children.black += cur.children.black;
	});
	
	std::int64_t total = 0;
	dfs(graph, [&](int parent, int node, std::int64_t weight) {
		if (parent == -1)
			return;

		auto b_count = nodes[node].children.black,
			 r_count = nodes[node].children.red;

		total = (total + (((r_count * (red_nodes - r_count))%MOD) * weight)%MOD)%MOD;
		total = (total + (((b_count * (black_nodes - b_count))%MOD) * weight)%MOD)%MOD;
	});

	//for(int i = 0; i < graph.size(); i++)
		//	std::cout << nodes[i].children.black << " " <<nodes[i].children.red << std::endl;
	std::cout << total << '\n';
	return 0;
}
