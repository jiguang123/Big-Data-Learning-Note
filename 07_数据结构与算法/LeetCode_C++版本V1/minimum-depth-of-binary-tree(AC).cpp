// 1WA, 1AC, good~
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
	// 1WA, only depths of leaf nodes count
    int minDepth(TreeNode *root) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if(root == nullptr){
            return 0;
        }
        
        result = INT_MAX;
        _minDepth(root, 1);
        return result;
    }
private:
    int result;
    
    const int &mymin(const int &x, const int &y) {
        return (x < y ? x : y);
    }
    
    int _minDepth(TreeNode *root, int depth) {
        if(root->left == nullptr && root->right == nullptr){
            if(depth < result){
                result = depth;
            }
        }
        
        if(root->left != nullptr){
            _minDepth(root->left, depth + 1);
        }
        if(root->right != nullptr){
            _minDepth(root->right, depth + 1);
        }
    }
};