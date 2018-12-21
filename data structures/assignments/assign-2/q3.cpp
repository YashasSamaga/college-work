#include <iostream>
#include <vector>
#include <utility>
#include <cstdint>

template <typename T, class Compare = std::less<T> >
class heap {
	public:
		T& top(); /* should return const T& */
		void push(const T& value);
		void pop();
		void clear() { data.clear(); }

		std::size_t size() const { return data.size(); }

		typename std::vector<T>::iterator begin() {
			return data.begin();
		}

		typename std::vector<T>::iterator end() {
			return data.end();
		}
	
	private:
		typedef typename std::vector<T>::size_type index_type;
		std::vector<T> data;
		index_type parent(index_type idx) {
			return (idx - 1) / 2;
		}
		index_type left(index_type idx) {
			return idx * 2 + 1;
		}
		index_type right(index_type idx) {
			return idx * 2 + 2;
		}
};

template <typename T, class Compare>
void heap<T, Compare>::push(const T& value) {
	Compare comp;
	data.resize(data.size() + 1);
	index_type child = data.size() - 1;
	while(child != 0 && comp(data[parent(child)], value)) {
		data[child] = std::move(data[parent(child)]);
		child = parent(child);
	}
	data[child] = value;
}

template <typename T, class Compare>
T& heap<T, Compare>::top() {
	return data.front();
}

template <typename T, class Compare>
void heap<T, Compare>::pop() {
	Compare comp;
	index_type parent = 0;
	while(left(parent) < data.size()) {
		index_type target = left(parent);
		if(right(parent) < data.size() && comp(data[target], data[right(parent)]))
			target = right(parent);

		if(comp(data[target], data.back()))
			break;
 
		data[parent] = data[target];
		parent = target;
	}
	data[parent] = data.back();
	data.pop_back();
}

template <typename ForwardItr, class Compare = std::less<typename ForwardItr::value_type> >
void heapsort(ForwardItr first, ForwardItr last) { /* TODO make inplace */
	heap<typename ForwardItr::value_type, Compare> hp;
	
	for(ForwardItr pos = first; pos != last; ++pos)
		hp.push(*pos);
	
	for(ForwardItr pos = first; pos != last; ++pos, hp.pop())
		*pos = hp.top();
}

/****************/
struct GF {
	int Di;
	int Ti;
	int Si;
};

struct GFCompare {
	bool operator()(const GF& a, const GF& b) {
		return a.Si < b.Si;
	}
};

struct GFCompareByDi {
	bool operator()(const GF& a, const GF& b) {
		return a.Di > b.Di;
	}
};

int main () {
	

	int T;
	std::cin >> T;

	std::vector<GF> gf;
	heap<GF, GFCompare> next;
	while(T--) {
		int N, D;
		std::cin >> N >> D;
		
		gf.clear();
		gf.reserve(N);
		next.clear();

		for(int i = 0; i < N; i++) {
			GF tmp;
			std::cin >> tmp.Di >> tmp.Ti >> tmp.Si;
			gf.push_back(tmp);
		}
		heapsort<std::vector<GF>::iterator, GFCompareByDi>(gf.begin(), gf.end()); //decltype(gf)::iterator

		int cur = 0;
		for(int day = 1; day <= D; day++) {
			while(cur < N && gf[cur].Di == day) {
				next.push(gf[cur]);
				cur++;				
			}
			if(next.size() == 0)
				continue;
			GF& top = next.top();
			top.Ti--;
			if(top.Ti == 0)
				next.pop();		
		}		
		
		std::uint64_t sadness = 0;
		for(auto itr = next.begin(); itr != next.end(); ++itr)
			sadness += static_cast<std::uint64_t>(itr->Ti) * (itr->Si);
		std::cout << sadness << '\n';
	}
	return 0;
}
