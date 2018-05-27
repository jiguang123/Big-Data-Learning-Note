// 17.13 Flatten a binary search tree into a doubly linked list by inorder traversal order.
// Use postorder traversal to do the flattening job.
#include <cstdio>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int _val = 0): val(_val), left(nullptr), right(nullptr) {};
};

void flatten(TreeNode *&root, TreeNode *&left_most, TreeNode *&right_most)
{
	if (root == nullptr) {
		left_most = right_most = nullptr;
		return;
	}
	
	TreeNode *ll, *lr, *rl, *rr;
	if (root->left != nullptr) {
		flatten(root->left, ll, lr);
		root->left = lr;
		lr->right = root;
	} else {
		ll = lr = root;
	}
	
	if (root->right != nullptr) {
		flatten(root->right, rl, rr);
		root->right = rl;
		rl->left = root;
	} else {
		rl = rr = root;
	}
	
	left_most = ll;
	right_most = rr;
}

void constructBinaryTree(TreeNode *&root)
{
	int val;
	
	if (scanf("%d", &val) != 1) {
		root = nullptr;
	} else if (val == 0) {
		root = nullptr;
	} else {
		root = new TreeNode(val);
		constructBinaryTree(root->left);
		constructBinaryTree(root->right);
	}
}

void deleteList(TreeNode *&head)
{
	TreeNode *ptr;
	
	while (head != nullptr) {
		ptr = head;
		head = head->right;
		delete ptr;
	}
}

int main()
{
	TreeNode *root;
	TreeNode *left_most, *right_most;
	TreeNode *head;
	TreeNode *ptr;
	
	while (true) {
		constructBinaryTree(root);
		if (root == nullptr) {
			break;
		}
		flatten(root, left_most, right_most);
		head = left_most;
		for (ptr = head; ptr != nullptr; ptr = ptr->right) {
			printf("%d ", ptr->val);
		}
		putchar('\n');
		deleteList(head);
	}
	
	return 0;
}