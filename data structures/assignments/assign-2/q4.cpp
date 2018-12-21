#include <iostream>
#include <vector>

template<typename T>
T max(T a, T b) {
	return (a > b) ? a : b;
}

template <typename T, class Compare = std::less<T>>
class AVLTree {
public:
	AVLTree(std::int64_t prime) : prime(prime) { root = nullptr; }

	void insert(T value) {
		root = insert(root, value);
	}

	void erase(T value) {
		root = erase(root, value);
	}

	bool empty() const { return root == nullptr; }
	std::size_t height() const { return height(root); }
	std::int64_t get_hash() const { return (root == nullptr) ? 0 : root->hash; }

	template <class UnaryPredicate>
	void inorder(UnaryPredicate) const;

	template <class UnaryPredicate>
	void preorder(UnaryPredicate) const;

	template <class UnaryPredicate>
	void postorder(UnaryPredicate) const;

private:
	struct Node {
		Node(const T& value) : value(value) { 
			height = count = 1;
			children = 0;
			left = right = nullptr;		
		}
		//TODO: add move constructor

		T value;
		int children; /* number of children in the subtree exclusive of itself */
		int count; /* duplicate count */
		int height;
		std::int64_t hash; /* inclusive of self */

		Node* left; /* TODO: <>_ptr? */
		Node* right;
	};
	Node* root; /* TODO: <>_ptr? */

	int height(Node *root) {
		return (root == nullptr) ? 0 : root->height;
	}
	
	template <class UnaryPredicate>
	void inorder(const Node* root, UnaryPredicate f) const {
		if (root == nullptr)
			return;
		inorder(root->left, f);
		f(root->value);
		inorder(root->right, f);
	}

	template <class UnaryPredicate>
	void preorder(const Node *root, UnaryPredicate f) const {
		if (root == nullptr)
			return;
		f(root->value);
		preorder(root->left, f);
		preorder(root->right, f);
	}

	template <class UnaryPredicate>
	void postorder(const Node *root, UnaryPredicate f) const {
		if (root == nullptr)
			return;
		postorder(root->left, f);
		postorder(root->right, f);
		f(root->value);
	}	

	int compute_children(Node *root) {
		if (root == nullptr)
			return 0; /* TODO: 0? throw? */
		int count = 0;
		if (root->left != nullptr)
			count += root->left->children + root->left->count;
		if (root->right != nullptr)
			count += root->right->children + root->right->count;
		return count;
	}

	const std::int64_t prime;
	const int MOD = 1000000000 + 7;
	std::int64_t compute_power(const int rank) {
		static std::vector<int64_t> powers(100000, 0); //TODO: std::array
		if (rank >= powers.size())
			powers.resize(rank*2, 0);
		if (powers[rank] == 0) {
			std::int64_t base = prime, exponent = rank, result = 1;
			while (exponent) {
				if (exponent % 2)
					result = (result * base) % MOD;
				base = (base * base) % MOD;
				exponent /= 2;
			}
			powers[rank] = result;
		}
		return powers[rank];
	}

	std::int64_t compute_hash(Node *root) {
		if(root == nullptr)
			return 0;
		std::int64_t result = 0;
		if (root->left == nullptr) {
			result = ((root->value * root->count)%MOD * compute_power(root->count))%MOD;
			if (root->right != nullptr) {
				result = (result + (root->right->hash * compute_power(root->count))%MOD)%MOD;
			}
		} else {
			result = root->left->hash; 
			result = (result + ((root->value * root->count)%MOD * compute_power(root->left->children + root->left->count + root->count))%MOD)%MOD;
			if (root->right != nullptr) {
				result = (result + (root->right->hash * compute_power(root->left->children + root->left->count + root->count))%MOD)%MOD;
			}	
		}
		return result%MOD;
	}

	Node* rotateRight(Node *root) {
		Node* z = root;
		Node* y = root->left;

		z->left = y->right;
		y->right = z;

		z->height = max(height(z->left), height(z->right)) + 1;
		y->height = max(height(y->left), height(y->right)) + 1;

		z->children = compute_children(z);
		y->children = compute_children(y);

		z->hash = compute_hash(z);
		y->hash = compute_hash(y);
		return y;
	}

	Node* rotateLeft(Node *root) {
		Node* z = root;
		Node* y = root->right;

		z->right = y->left;
		y->left = z;

		z->height = max(height(z->left), height(z->right)) + 1;
		y->height = max(height(y->left), height(y->right)) + 1;

		z->children = compute_children(z);
		y->children = compute_children(y);

		z->hash = compute_hash(z);
		y->hash = compute_hash(y);
		return y;
	}

	Compare comp;
	Node* insert(Node *root, T& value) {
		if (root == nullptr) {
			Node *ptr = new Node(value);
			ptr->hash = compute_hash(ptr);
			return ptr;
		}

		if (comp(value, root->value)) {
			root->left = insert(root->left, value);
			root->children = compute_children(root);
			root->hash = compute_hash(root);
			if (height(root->left) - height(root->right) > 1) { /* imbalance check */
				if (comp(value, root->left->value)) {
					root = rotateRight(root);
				} else {
					root->left = rotateLeft(root->left);
					root = rotateRight(root);
				}
			}
		} else if (comp(root->value, value)) {
			root->right = insert(root->right, value);
			root->children = compute_children(root);
			root->hash = compute_hash(root);
			if (height(root->right) - height(root->left) > 1) { /* imbalance check */
				if (comp(root->right->value, value)) {
					root = rotateLeft(root);
				} else {
					root->right = rotateRight(root->right);
					root = rotateLeft(root);
				}
			}
		} else {
			root->count++;
			root->hash = compute_hash(root);
			return root;
		}
		root->height = max(height(root->left), height(root->right)) + 1;
		root->children = compute_children(root);
		root->hash = compute_hash(root);
		return root;
	}
	Node* erase(Node* root, T& value) {
		if (root == nullptr)
			return nullptr;

		if (comp(value, root->value)) {
			root->left = erase(root->left, value);
		} else if (comp(root->value, value)) {
			root->right = erase(root->right, value);
		} else {
			if (--root->count > 0) {
				root->hash = compute_hash(root);
				return root;
			}
			if (root->left == nullptr && root->right == nullptr) { /* TODO: reorder branches for common-case first */
				delete root;
				return nullptr;
			} else if (root->left == nullptr || root->right == nullptr) {
				Node* temp = (root->left == nullptr) ? root->right : root->left;
				delete root;
				return temp;
			} else {
				Node* temp = root->right; /* find minimum in the right subtree */
				while (temp->left != nullptr)
					temp = temp->left;

				/* copy important information */
				root->value = temp->value; //TODO: useless full copy; std::move?! but see next line
				root->count = temp->count;
				temp->count=1;
				root->right = erase(root->right, temp->value);
				/* no return - node has subtrees and they have to be balanced */
			}
		}

		if (root == nullptr)
			return nullptr;

		if (height(root->left) - height(root->right) > 1) { /* imbalance check */
			if (height(root->left->left) - height(root->left->right) >= 0) {
				root = rotateRight(root);
			} else {
				root->left = rotateLeft(root->left);
				root = rotateRight(root);
			}
		} else if (height(root->right) - height(root->left) > 1) { /* imbalance check */
			if (height(root->right->right) - height(root->right->left) >= 0) {
				root = rotateLeft(root);
			} else {
				root->right = rotateRight(root->right);
				root = rotateLeft(root);
			}
		}
		root->height = max(height(root->left), height(root->right)) + 1;
		root->children = compute_children(root);
		root->hash = compute_hash(root);
		return root;
	}
};

template <typename T, class Compare>
template <class UnaryPredicate>
void AVLTree<T, Compare>::inorder(UnaryPredicate f) const { inorder(root, f); }

template <typename T, class Compare>
template <class UnaryPredicate>
void AVLTree<T, Compare>::preorder(UnaryPredicate f) const { preorder(root, f); }

template <typename T, class Compare>
template <class UnaryPredicate>
void AVLTree<T, Compare>::postorder(UnaryPredicate f) const { postorder(root, f); }

int main () {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	int Q, P;
	std::cin >> Q >> P;

	AVLTree<std::int64_t> tree(P);
	while(Q--) {
		char op;
		std::cin >> op;

		switch(op) {
			case 'A':
			{
				int n;
				std::cin >> n;
				tree.insert(n);
				break;
			}
			case 'D':
			{
				int n;
				std::cin >> n;
				tree.erase(n);
				break;
			}
			case 'H':
				std::cout << tree.get_hash() << '\n';
				break;
		}
	}
	return 0;
}

