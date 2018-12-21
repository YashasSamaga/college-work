#include <iostream>
#include <vector>
#include <cstdlib>

//#define DEBUG

struct Edge {
	int target;
	int weight;
};

std::int64_t fast_exp(std::int64_t base, std::int64_t exponent, int MOD = 1000000000 + 7) {
	std::int64_t result = 1;
	while (exponent) {
		if (exponent % 2)
			result = (result * base) % MOD;
		base = (base * base) % MOD;
		exponent /= 2;
	}
	return result;
}

std::vector<Edge> graph[100001];
std::vector<bool> visited[100001];
bool unhappy[100001];

void dfs(int parent, int idx) {
	int node = graph[parent][idx].target;

	unhappy[node] = true;
	visited[parent][idx] = true;
	
	for (int i = 0; i < graph[node].size(); i++) {
		if (parent != graph[node][i].target && visited[node][i] == false)
			dfs(node, i);
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;

	for (int i = 1; i < N; i++) {
		int a, b, w;
		std::cin >> a >> b >> w;
		a--; b--;
		graph[a].push_back({ b, w });
		graph[b].push_back({ a, w });
	}

	for (int i = 0; i < N; i++) {
		qsort(graph[i].data(), graph[i].size(), sizeof(Edge), [](const void* a, const void* b) {
			const Edge *e1 = reinterpret_cast<const Edge*>(a),
				       *e2 = reinterpret_cast<const Edge*>(b);
			return e1->weight - e2->weight;
		});
	}
	
	for (int i = 0; i < N; i++)
		visited[i].resize(graph[i].size(), false);

	for (int i = 0; i < N; i++) {
		for (int j = 1; j < graph[i].size(); j++) {
			if (graph[i][j - 1].weight == graph[i][j].weight) {
				if (visited[i][j] == false)
					dfs(i, j);
				if (visited[i][j - 1] == false)
					dfs(i, j - 1);
			}
		}
	}

	int total = 0;
	for (int i = 0; i < N; i++)
		if (unhappy[i] == true)
			total++;

	total = N - total;
	if(total == 0) {
		std::cout << 0;
		return 0;
	}

	std::int64_t answer = fast_exp(total, total, 1000000000 + 6);
	std::cout << fast_exp(total, answer, 1000000000 + 7);
	return 0;
}
