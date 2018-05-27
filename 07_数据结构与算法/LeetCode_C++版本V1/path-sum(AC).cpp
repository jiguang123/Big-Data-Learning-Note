/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool hasPathSum(TreeNode *root, int sum) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
		if(root == nullptr){
			return false;
		}

		if(root->left == nullptr){
			if(root->right == nullptr){
				return root->val == sum;
			}else{
				return hasPathSum(root->right, sum - root->val);
			}
		}else{
			if(root->right == nullptr){
				return hasPathSum(root->left, sum - root->val);
			}else{
				return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
			}
		}
    }
};