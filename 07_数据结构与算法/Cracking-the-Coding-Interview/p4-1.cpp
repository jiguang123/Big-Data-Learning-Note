// 4.1 Implement an algorithm to check if a bianry tree is height-balanced.
#include <algorithm>
#include <cstdio>
#include <unordered_map>
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

void calcHeights(TreeNode *root, unordered_map<TreeNode *, int> &heights)
{
	if (root == nullptr) {
		heights[root] = 0;
	} else {
		calcHeights(root->left, heights);
		calcHeights(root->right, heights);
		heights[root] = max(heights[root->left], heights[root->right]) + 1;
	}
}

bool isBalanced(TreeNode *root, unordered_map<TreeNode *, int> &heights)
{
	if (root == nullptr) {
		return true;
	} else {
		return abs(heights[root->left] - heights[root->right]) <= 1;
	}
}

int main()
{
	TreeNode *root;
	unordered_map<TreeNode *, int> heights;
	
	while (true) {
		constructBinaryTree(root);
		if (root == nullptr) {
			break;
		}
		
		calcHeights(root, heights);
		if (isBalanced(root, heights)) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
		heights.clear();
		clearBinaryTree(root);
	}
	
	return 0;
}