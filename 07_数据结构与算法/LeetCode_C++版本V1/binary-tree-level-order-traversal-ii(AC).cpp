// 1CE, 1AC, when copying the code, make sure you don't mix up the name of function and variables!!
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
	//1CE here, levelOrder, levelOrderBottom, check the names before you copy the codes!!!!
	// That was stupid, man~
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
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

		vector<int> tmp;
		int i = 0;
		while(i < result.size() - 1 - i){
			tmp = result[i];
			result[i] = result[result.size() - 1 - i];
			result[result.size() - 1 - i] = tmp;
			++i;
		}
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