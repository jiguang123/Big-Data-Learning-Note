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
    TreeNode *sortedArrayToBST(vector<int> &num) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
		if(num.size() <= 0){
			return nullptr;
		}else{
			return constructBSTFromArray(num, 0, (int)(num.size() - 1));
		}
    }
private:
	TreeNode *constructBSTFromArray(vector<int> &num, int left, int right) {
		int mid;
		TreeNode* root;
		
		if(left > right){
			return nullptr;
		}
		
		mid = (right - left) / 2 + left;
		root = new TreeNode(num[mid]);
		root->left = constructBSTFromArray(num, left, mid - 1);
		root->right = constructBSTFromArray(num, mid + 1, right);
		
		return root;
	}
};