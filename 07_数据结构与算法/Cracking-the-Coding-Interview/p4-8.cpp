// 4.8 Check if a tree is a subtree of another.
#include <cstdio>
#include <unordered_map>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	
	TreeNode(int _val = 0): val(_val), left(nullptr), right(nullptr) {};
};

void constructTree(TreeNode *&root)
{
	int val;
	
	scanf("%d", &val);
	if (val == 0) {
		root = nullptr;
	} else {
		root = new TreeNode(val);
		constructTree(root->left);
		constructTree(root->right);
	}
}

int countNode(TreeNode *root, unordered_map<TreeNode *, int> &node_count)
{
	if (root == nullptr) {
		return 0;
	} else {
		node_count[root] = countNode(root->left, node_count) + countNode(root->right, node_count) + 1;
		return node_count[root];
	}
}

bool isIdentical(TreeNode *root1, TreeNode *root2)
{
	if (root1 == nullptr) {
		return root2 == nullptr;
	} else if (root2 == nullptr) {
		return false;
	}
	
	if (root1->val != root2->val) {
		return false;
	}
	
	return isIdentical(root1->left, root2->left) && isIdentical(root1->right, root2->right);
}

bool hasSubtree(TreeNode *root1, TreeNode *root2, unordered_map<TreeNode *, int> &node_count)
{
	if (root1 == nullptr || root2 == nullptr) {
		return false;
	}
	
	if (node_count[root1] < node_count[root2]) {
		return false;
	} else if (node_count[root1] > node_count[root2]) {
		return hasSubtree(root1->left, root2, node_count) || hasSubtree(root1->right, root2, node_count);
	} else {
		return isIdentical(root1, root2);
	}
}

void clearTree(TreeNode *&root)
{
	if (root == nullptr) {
		return;
	}
	clearTree(root->left);
	clearTree(root->right);
	delete root;
	root = nullptr;
}

int main()
{
	TreeNode *root1, *root2;
	unordered_map<TreeNode *, int> node_count;
	
	while (true) {
		constructTree(root1);
		if (root1 == nullptr) {
			break;
		}
		constructTree(root2);
		if (root2 == nullptr) {
			break;
		}
		
		countNode(root1, node_count);
		countNode(root2, node_count);
		if(hasSubtree(root1, root2, node_count)) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
		
		node_count.clear();
		clearTree(root1);
		clearTree(root2);
	}
	
	return 0;
}