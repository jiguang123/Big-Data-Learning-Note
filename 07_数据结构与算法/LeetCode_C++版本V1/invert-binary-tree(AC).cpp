// 1AC, a joke?
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *	 int val;
 *	 TreeNode *left;
 *	 TreeNode *right;
 *	 TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
	TreeNode* invertTree(TreeNode* root) {
		if (root == NULL) {
			return NULL;
		}
		TreeNode *p = root->left;
		root->left = root->right;
		root->right = p;
		invertTree(root->left);
		invertTree(root->right);
		
		return root;
	}
};