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
    vector<int> inorderTraversal(TreeNode *root) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
		res.clear();
		if(root == nullptr){
			return res;
		}
		
		inorder(root);
		
		return res;
    }
private:
	vector<int> res;
	void inorder(TreeNode *root) {
		if(root == nullptr){
			return;
		}else{
			if(root->left != nullptr){
				inorder(root->left);
			}
			res.push_back(root->val);
			if(root->right != nullptr){
				inorder(root->right);
			}
		}
	}
};