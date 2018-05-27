// 1AC, easy with recursive
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
    vector<int> rightSideView(TreeNode *root) {
        vector<int> res;
        if (root == nullptr) {
            return res;
        }
        
        dfs(root, 1, res);
        return res;
    }
private:
    void dfs(TreeNode *ptr, int dep, vector<int> &res) {
        if (dep > res.size()) {
            res.push_back(ptr->val);
        }
        
        if (ptr->right != nullptr) {
            dfs(ptr->right, dep + 1, res);
        }
        if (ptr->left != nullptr) {
            dfs(ptr->left, dep + 1, res);
        }
    }
};