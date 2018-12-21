#include <iostream>
#include <vector>

struct Gear {
	Gear() : state(State::disconnected) {	}

	int x;
	int y;
	int r;

	struct { int numer, denom; } speed; /* std::ratio allowed?! */

	enum class State {
		disconnected,
		stuck,
		moving
	} state;	
};

typedef typename std::vector<std::vector<std::size_t> > Graph;

template <typename Func>
void dfs_util(Graph& graph, std::vector<bool>& visited, Func f, int parent, int node) {
	f(parent, node);

	if(visited[node] == true)
		return;

	visited[node] = true;

	for(int to = 0; to < graph[node].size(); to++)
		dfs_util(graph, visited, f, node, graph[node][to]);	
}

template <typename Func>
void dfs(Graph& graph, Func f) {
	std::vector<bool> visited(graph.size(), false);
	dfs_util(graph, visited, f, -1, 0);
}

bool distance_equal(int x1, int y1, int x2, int y2, int dist) {
	return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) == dist*dist;
}

template <typename T>
bool equal_ratio(T n1, T d1, T n2, T d2) {
	return n1*d2 == n2*d1;
}

template <typename T>
T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
}

template <typename T>
bool reduce_fraction(T& numer, T& denom) {
	T hcf = gcd(std::abs(numer), denom);
	numer /= hcf;
	denom /= hcf;
}

int main () {
	int n;
	std::cin>>n;

	std::vector<Gear> gears(n);
	for(int i = 0; i < n; i++)
		std::cin >> gears[i].x >> gears[i].y >> gears[i].r;

	std::vector<std::vector<std::size_t> > graph(n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if(distance_equal(gears[i].x, gears[i].y, gears[j].x, gears[j].y, gears[i].r + gears[j].r))	
				graph[i].push_back(j);

	gears[0].state = Gear::State::moving; /* input gear is moving by default */
	gears[0].speed.numer = 
	gears[0].speed.denom = 1;
	
	bool stuck = false;
	dfs(graph, [&](int parent, int node) {
		if(parent == -1)
			return;

		if(gears[parent].state == Gear::State::disconnected)
			throw; /* should not happen */

		if(gears[parent].state == Gear::State::stuck) {
			gears[node].state = Gear::State::stuck;
			return;
		}

		if(gears[node].state == Gear::State::stuck) {
			gears[parent].state = Gear::State::stuck;
			return;
		}

		int expected_numer = (-1) * gears[parent].speed.numer * gears[parent].r,
		    expected_denom = gears[parent].speed.denom * gears[node].r;

		if(gears[node].state == Gear::State::moving) {
			if(!equal_ratio(gears[node].speed.numer, gears[node].speed.denom, expected_numer, expected_denom)) {
				gears[node].state = gears[parent].state = Gear::State::stuck;
				stuck = true;
				return;
			}				
		}

		reduce_fraction(expected_numer, expected_denom);

		gears[node].state = Gear::State::moving;
		gears[node].speed.numer = expected_numer;
		gears[node].speed.denom = expected_denom;		
	});

	if(stuck) {
		std::cout << "The input gear cannot move.";
		return 0;
	}		

	auto last_gear = gears.back();
	if(last_gear.state == Gear::State::disconnected) {
		std::cout << "The input gear is not connected to the output gear.";
		return 0;
	}
	std::cout << last_gear.speed.numer << ':' << last_gear.speed.denom;
	return 0;
}
