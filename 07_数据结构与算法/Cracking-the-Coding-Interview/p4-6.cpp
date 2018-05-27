// 4.6 Find the inorder successor of a node in the binary tree.
// offline algorithm with inorder traversal.
#include <cstdio>
#include <unordered_map>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;
	
	TreeNode(int _val = 0): val(_val), left(nullptr), right(nullptr), parent(nullptr) {};
};

void constructBinaryTree(TreeNode *&root)
{
	int val;
	
	scanf("%d", &val);
	if (val <= 0) {
		root = nullptr;
	} else {
		root = new TreeNode(val);

		constructBinaryTree(root->left);
		constructBinaryTree(root->right);
		if (root->left != nullptr) {
			root->left->parent = root;
		}
		if (root->right != nullptr) {
			root->right->parent = root;
		}
	}
}

void inorderTraversal(TreeNode *root, vector<TreeNode *> &inorder_list)
{
	if (root == nullptr) {
		return;
	}
	inorderTraversal(root->left, inorder_list);
	inorder_list.push_back(root);
	inorderTraversal(root->right, inorder_list);
}

TreeNode *inorderSuccessor(TreeNode *node, unordered_map<TreeNode *, TreeNode *> &dict)
{
	if (dict.find(node) == dict.end()) {
		return nullptr;
	} else {
		return dict[node];
	}
}

void clearBinaryTree(TreeNode *&root) {
	if (root == nullptr) {
		return;
	} else {
		clearBinaryTree(root->left);
		clearBinaryTree(root->right);
		delete root;
		root = nullptr;
	}
}

int main()
{
	TreeNode *root;
	unordered_map<TreeNode *, TreeNode *> dict;
	vector<TreeNode *> inorder_list;
	int i;
	
	while (true) {
		constructBinaryTree(root);
		if (root == nullptr) {
			break;
		}
		
		inorderTraversal(root, inorder_list);
		for (i = 0; i < (int)inorder_list.size() - 1; ++i) {
			dict[inorder_list[i]] = inorder_list[i + 1];
		}
		dict[inorder_list[i]] = nullptr;
		
		TreeNode *next_node;
		for (i = 0; i < (int)inorder_list.size(); ++i) {
			next_node = inorderSuccessor(inorder_list[i], dict);
			if (next_node != nullptr) {
				printf("%d %d\n", inorder_list[i]->val, next_node->val);
			} else {
				printf("%d #\n", inorder_list[i]->val);
			}
		}
		
		inorder_list.clear();
		dict.clear();
		clearBinaryTree(root);
	}
	
	return 0;
}