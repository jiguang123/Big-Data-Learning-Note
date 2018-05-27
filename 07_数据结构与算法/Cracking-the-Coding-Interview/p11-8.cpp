// 11.8 Given an array of integers, find out for a given value, how many integers are there in the array, that are no greater than the value.
// If the value is not in the array, return -1 instead.
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

struct TreeNode {
	int val;
	int count;
	int count_left;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int _val = 0): val(_val), count(1), count_left(0), left(nullptr), right(nullptr) {};
};

void insertNode(TreeNode *&root, int val)
{
	if (root == nullptr) {
		root = new TreeNode(val);
	} else if (val == root->val) {
		++(root->count);
	} else if (val < root->val) {
		++(root->count_left);
		insertNode(root->left, val);
	} else {
		insertNode(root->right, val);
	}
}

int getRank(TreeNode *root, int val)
{
	int result;
	TreeNode *ptr;
	
	result = 0;
	ptr = root;
	while (ptr != nullptr) {
		if (ptr->val > val) {
			ptr = ptr->left;
		} else if (ptr->val < val) {
			result += ptr->count_left + 1;
			ptr = ptr->right;
		} else {
			break;
		}
	}
	if (ptr != nullptr) {
		result += ptr->count_left;
		return result;
	} else {
		return -1;
	}
}

void clearTree(TreeNode *&root)
{
	if (root != nullptr) {
		clearTree(root->left);
		clearTree(root->right);
		delete root;
		root = nullptr;
	}
}

int main()
{
	int val;
	TreeNode *root;
	string s;
	
	root = nullptr;
	while (cin >> s) {
		if (s == "i") {
			cin >> val;
			insertNode(root, val);
		} else if (s == "r") {
			cin >> val;
			printf("rank = %d\n", getRank(root, val));
		} else if (s == "e") {
			break;
		}
	}
	clearTree(root);
	
	return 0;
}