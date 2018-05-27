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
    int maxDepth(TreeNode *root) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
		if(root == NULL){
			return 0;
		}else{
			return 1 + mymax(maxDepth(root->left), maxDepth(root->right));
		}
    }
private:
	const int &mymax(const int &a, const int &b) {
		return (a > b ? a : b);
	}
};