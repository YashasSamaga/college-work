#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>

const int max = 3 * 100000 + 10;
const int bits = 30;

int trie[max * bits][2], count[max * bits], idx = 1;
void insert(unsigned int num) {
	int cur = 0;
	for(int i = bits; i >= 0; i--) {
		int bit = (num >> i) & 1;
		
		if(trie[cur][bit] == 0) {
			trie[cur][bit] = idx;			
			idx++;
		}
		cur = trie[cur][bit];
		count[cur]++;
	}
}


int best(unsigned int num) {
	int cur = 0, result = 0;
	for(int i = bits; i >= 0; i--) {
		int bit = (num >> i) & 1;
		
		if(trie[cur][bit] == 0) {
			cur = trie[cur][!bit];
			result |= (!bit) << i;
		} else {
			cur = trie[cur][bit];
			result |= (bit) << i;
		}
	}
	return result;
}

int erase(unsigned int num, int i, int cur) {
	if(i == -1) {
		count[cur]--;
		return ((count[cur] == 0) ? 0 : cur);
	}

	int bit = (num >> i) & 1;		
	trie[cur][bit] = erase(num, i - 1, trie[cur][bit]);
	count[cur]--;	
	return ((trie[cur][!bit] + trie[cur][bit] == 0 && count[cur] == 0) ? 0 : cur);
}

int main () {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	int N;
	std::cin >> N;
	
	std::vector<int> E(N);
	for(int i = 0; i < N; i++) {
		std::cin >> E[i];
	}

	for(int i = 0; i < N; i++) {
		unsigned int tmp;
		std::cin >> tmp;
		insert(tmp);
	}

	for(auto tmp : E) {
		unsigned int x = best(tmp);
		erase(x, bits, 0);
		std::cout << (x ^ tmp) << " ";
	}
	return 0;
}
