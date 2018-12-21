#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

struct Edge {
	Edge(int from, int to, int weight) : from(from), to(to), weight(weight) { }
	int from;
	int to;
	int weight;
	
	bool operator<(const Edge& rhs) const {
		return weight < rhs.weight;
	}
	
	bool operator>(const Edge& rhs) const {
		return weight > rhs.weight;
	}
};

class disjoint_sets {
	public:
		disjoint_sets(int N) : S(N, -1) { }
		
		int get_key(int key) {
			if(S[key] < 0) {
				return key;
			} else {
				S[key] = get_key(S[key]);
				return S[key];
			}		
		}

		int join(int comp1, int comp2) {
			if(S[comp2] < S[comp1]) {
				S[comp1] = comp2;
				return comp2;
			} else if(S[comp1] < S[comp2]) {
				S[comp2] = comp1;
				return comp1;
			} else {
				S[comp1]--;
				S[comp2] = comp1;
				return comp1;
			} 
		}
		
	private:
		std::vector<int> S;
};

int main () {
	int N, M;
	std::cin >> N >> M;
	
	std::vector<int> values(N);
	for(int i = 0; i < N; i++)
		std::cin >> values[i];	
	
	std::vector<Edge> edges;
	for(int i = 0; i < M; i++) {
		int from, to;
		std::cin >> from >> to;	
		edges.emplace_back(from - 1, to - 1, std::min(values[from - 1], values[to - 1]));
	}
	
	disjoint_sets sets(N);
	std::vector<int> count(N, 1);
	
	constexpr int64_t MOD = 1000000000 + 7;
	int64_t sum = 0;
	std::sort(edges.begin(), edges.end(), std::greater<Edge>());
	
	for(const auto& edge : edges) {
		int key_from = sets.get_key(edge.from),
			key_to = sets.get_key(edge.to);

		if(key_from == key_to)
			continue;
			
		int count_from = count[key_from],
			count_to = count[key_to];
		sum += (edge.weight * (count_from * count_to)) % MOD;
		
		int key_combined = sets.join(key_from, key_to);	
		assert(sets.get_key(edge.from) == key_combined && sets.get_key(edge.to) == key_combined);
		count[key_combined] = count_from + count_to;
	}
	std::cout << (sum * 2) % MOD;
	return 0;
}
