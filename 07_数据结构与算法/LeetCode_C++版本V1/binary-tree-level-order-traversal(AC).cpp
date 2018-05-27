// 3CE, 1AC, you fool!!! The code must be bug-free, well.. at least it should compile and runnnnnnnnnnn!
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
    vector<vector<int> > levelOrder(TreeNode *root) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        // I could use pre-order traversal to do this.
		// Level-order traversal makes sense too.
		
		// 1CE here, declaration of int i is MISSSING
		for(int i = 0; i < result.size(); ++i){
			result[i].clear();
		}
		result.clear();
		
		if(root == nullptr){
			return result;
		}
		
		preOrder(root, 0);
		return result;
    }
private:
	vector<vector<int>> result;
	
	void preOrder(TreeNode *root, int height) {
		if(root == nullptr){
			return;
		}
		// 1CE here,  ) MISSING!!!
		while(result.size() <= height){
			result.push_back(vector<int>());
		}
		result[height].push_back(root->val);
		
		if(root->left != nullptr){
			preOrder(root->left, height + 1);
		}
		if(root->right != nullptr){
			// 1CE here, spelling error, pre-order preOrder
			// Don't rely on auto-complete, you're spoiled!!!
			preOrder(root->right, height + 1);
		}
	}
};