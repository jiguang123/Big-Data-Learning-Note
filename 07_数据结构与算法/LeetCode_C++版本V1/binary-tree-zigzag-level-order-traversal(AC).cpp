// 1AC, excellent!!
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
    vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
		int i;
		
		for(i = 0; i < result.size(); ++i){
			result[i].clear();
		}
		result.clear();
		
		if(root == nullptr){
			return result;
		}
		
		preOrder(root, 0);
		
		for(i = 0; i < result.size(); ++i){
		    if(i % 2){
		        reverse(result[i], 0, result[i].size() - 1);
		    }
		}
		
		return result;
    }
private:
	vector<vector<int>> result;
	
	void preOrder(TreeNode *root, int height) {
		if(root == nullptr){
			return;
		}
		while(result.size() <= height){
			result.push_back(vector<int>());
		}
		result[height].push_back(root->val);
		
		if(root->left != nullptr){
			preOrder(root->left, height + 1);
		}
		if(root->right != nullptr){
			preOrder(root->right, height + 1);
		}
	}
	
	void reverse(vector<int> &num, int left, int right) {
	    int i;
	    
	    if(left >= right){
	        return;
	    }
	    
	    int tmp;
	    i = left;
	    while(i < left + right - i){
	        tmp = num[i];
	        num[i] = num[left + right - i];
	        num[left + right - i] = tmp;
	        ++i;
	    }
	}
};