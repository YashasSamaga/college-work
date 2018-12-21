#include <iostream>
#include <iterator>

class Trie {
	public:
		void insert(const std::string& str) { insert(&root, str); }
		int match_count(const std::string& str, int marker) { return match_count(&root, str, marker); }
	private:
		struct Node {
			Node() {
				std::fill(child, std::end(child), nullptr);
				isEndOfWord = 0;
				marker = 0;
			}
			Node *child[5]; //a, b, c, d, e
			int isEndOfWord;
			int marker;
		};
		Node root;
		void insert(Node* root, const std::string& str) {
			for(auto c : str) {
				const int idx = c - 'a';
				if(root->child[idx] == nullptr)
					root->child[idx] = new Node();
				root = root->child[idx];		
			}
			root->isEndOfWord++;
		}
		int match_count(Node* root, const std::string& str, int marker, int pos = 0) {
			if(root == nullptr)
				return 0;

			if(pos == str.size()) {
				if(root->marker == marker)
					return 0;
				root->marker = marker;
				return root->isEndOfWord;
			}

			char c = str[pos];
			if(c == '?') {
				int count = 0;
				for(int i = 0; i < 5; i++)
					count += match_count(root->child[i], str, marker, pos + 1);
				count += match_count(root, str, marker, pos + 1);
				return count;
			} else {
				return match_count(root->child[c - 'a'], str, marker, pos + 1);
			}
		}
};

int main () {
	int N;
	std::cin >> N;

	Trie names;
	std::string str;
	for(int i = 0; i < N; i++) {		
		std::cin >> str;
		names.insert(str);
	}

	int Q;
	std::cin >> Q;
	for(int i = 0; i < Q; i++) {
		std::cin >> str;
		std::cout << names.match_count(str, i + 1) << '\n';
	}
	return 0;
}
