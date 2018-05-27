// 4.5 Check if a binary tree is binary search tree.
#include <cstdio>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	
	TreeNode(int _val = 0): val(_val), left(nullptr), right(nullptr) {};
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
	}
}

bool postorderTraversal(TreeNode *root, TreeNode *&left_most, TreeNode *&right_most)
{
	TreeNode *ll, *lr, *rl, *rr;
	bool res_left = true, res_right = true;
	
	if (root->left != nullptr) {
		if (!postorderTraversal(root->left, ll, lr)) {
			return false;
		}
		if (lr->val >= root->val) {
			// all left nodes must be smaller than the root.
			return false;
		}
	} else {
		ll = lr = root;
	}
	
	if (root->right != nullptr) {
		if (!postorderTraversal(root->right, rl, rr)) {
			return false;
		}
		if (rl->val <= root->val) {
			// all right nodes must be greater than the root.
			return false;
		}
	} else {
		rl = rr = root;
	}
	left_most = ll;
	right_most = rr;
	
	return true;
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
	TreeNode *left_most, *right_most;
	
	while (true) {
		constructBinaryTree(root);
		if (root == nullptr) {
			break;
		}
		
		left_most = right_most = nullptr;
		if (postorderTraversal(root, left_most, right_most)) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
		
		clearBinaryTree(root);
	}
	
	return 0;
}