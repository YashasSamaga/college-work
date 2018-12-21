#include <iostream>
#include <string>
#include <vector>
#include <iterator>

struct Node {
	Node(int steps) {
		std::fill(child, std::end(child), nullptr);
		this->steps = steps;
	}

	Node *child[26];
	int steps;
};

void insert(Node *root, const std::string& str) {
	int null_index = 0;
	while (null_index < str.size() && root->child[str[null_index] - 'a'] != nullptr) {
		root = root->child[str[null_index] - 'a'];
		null_index++;
	}

	for (int i = null_index, steps = root->steps; i < str.size(); i++) {
		int actual_size = str.size() - null_index,
			actual_index = i - null_index;

		if (actual_size % 2 == 0) { /* even */
			if (actual_index <= actual_size / 2)
				steps++;
			else
				steps--;
		}
		else { /* odd */
			if (actual_index <= actual_size / 2)
				steps++;
			else if (actual_index - 1 > actual_size / 2)
				steps--;
		}
		const int idx = str[i] - 'a';
		root = root->child[idx] = new Node(steps);
	}
}

int calculate_steps(Node *root, const std::string& str) {
	for (int i = 0; i < str.size(); i++) {
		const int idx = str[i] - 'a';
		if (root->child[idx] == nullptr)
			return root->steps + (str.size() - i);
		root = root->child[idx];
	}
	return root->steps;
}

int main() {
	int M, N;
	std::cin >> M >> N;

	Node* root = new Node(0);
	for (int i = 0; i < M; i++) {
		static std::string word;
		std::cin >> word;
		insert(root, word);
	}

	for (int i = 0; i < N; i++) {
		static std::string query;
		std::cin >> query;
		std::cout << calculate_steps(root, query) << '\n';
	}
	return 0;
}