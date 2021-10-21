#pragma once

#include <vector>
#include <cassert>

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