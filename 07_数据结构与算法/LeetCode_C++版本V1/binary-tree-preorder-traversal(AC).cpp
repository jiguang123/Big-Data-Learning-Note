// 1WA, 1RE, 1AC
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
    vector<int> preorderTraversal(TreeNode *root) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        result.clear();
        // 1WA here, this sentence missing
        preorder(root);
        return result;
    }
private:
    vector<int> result;
    
    void preorder(TreeNode *root) {
        // 1RE here, if(root)
        if(root == nullptr){
            return;
        }
        result.push_back(root->val);
        preorder(root->left);
        preorder(root->right);
    }
};