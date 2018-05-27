// 4.6 Find the inorder successor of a node in the binary tree.
// online algorithm with parent pointer.
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

TreeNode *inorderSuccessor(TreeNode *node)
{
	if (node == nullptr) {
		return nullptr;
	}
	
	TreeNode *result;
	if (node->right != nullptr) {
		result = node->right;
		while (result->left != nullptr) {
			result = result->left;
		}
		
		return result;
	} else {
		result = node;
		while(true) {
			if (result->parent == nullptr) {
				return nullptr;
			} else if (result == result->parent->left) {
				return result->parent;
			} else {
				result = result->parent;
			}
		}
	}
}

void inorderTraversal(TreeNode *root)
{
	if (root == nullptr) {
		return;
	}
	
	inorderTraversal(root->left);
	TreeNode *next_node = inorderSuccessor(root);
	if (next_node != nullptr) {
		printf("%d %d\n", root->val, next_node->val);
	} else {
		printf("%d #\n", root->val);
	}
	inorderTraversal(root->right);
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
	
	while (true) {
		constructBinaryTree(root);
		if (root == nullptr) {
			break;
		}
		
		inorderTraversal(root);
		
		clearBinaryTree(root);
	}
	
	return 0;
}