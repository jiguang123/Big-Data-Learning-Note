// 1AC, good~
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
    bool isBalanced(TreeNode *root) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
		if(root == nullptr){
			return true;
		}
		
		return myabs(treeHeight(root->left) - treeHeight(root->right)) <= 1 && isBalanced(root->left) && isBalanced(root->right);
    }
private:
	const int &myabs(const int &num) {
		return (num >= 0 ? num : -num);
	}
	
	const int &mymax(const int &x, const int &y) {
		return (x > y ? x : y);
	}
	
	int treeHeight(TreeNode *root) {
		if(root == nullptr){
			return 0;
		}else{
			return mymax(treeHeight(root->left), treeHeight(root->right)) + 1;
		}
	}
};