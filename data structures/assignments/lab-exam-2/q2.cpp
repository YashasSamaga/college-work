#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>

std::string str;
class fake_string {
	public:
		fake_string(int i, int j) : first(i), last(j) { }
		bool operator<(const fake_string& fs) const {
			if((last - first) != (fs.last - fs.first))
				return (last - first) < (fs.last - fs.first);

			for(int i = 0; i < (last - first); i++) {
				if(str[first + i] != str[fs.first + i])
					return str[first + i] < str[fs.first + i];
			}
			return false;
		}	
	int first, last;

};

int main () {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	std::cin >> str;

	std::string allowed;
	std::cin >> allowed;

	bool valid[26];
	std::fill_n(valid, 26, false);
	for(int i = 0; i < allowed.size(); i++) {
		if(allowed[i] == '1') {
			valid[i] = true;
		}
	}
	
	int K;
	std::cin >> K;

	std::set<fake_string> result;

	int bad = 0;
	for(int i = 0; i < str.size(); i++) {
		int bad = 0;
		for(int j = i; j < str.size(); j++) {
			if(!valid[str[j] - 'a'])			
				bad++;

			if(bad > K)
				break;

			result.emplace(i, j + 1);
		}	
	}
	
	std::cout << result.size();
	return 0;
}
