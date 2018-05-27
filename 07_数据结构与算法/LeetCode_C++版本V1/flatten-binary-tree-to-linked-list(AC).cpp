// 4WA, 1AC, not so easy.
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
    void flatten(TreeNode *root) {
        if (root == nullptr) {
            return;
        }
        
        if (root->left == nullptr && root->right == nullptr) {
            return;
        }
        
        TreeNode *left_most, *right_most;
        
        flattenRecursive(root, left_most, right_most);
    }
private:
    void flattenRecursive(TreeNode *root, TreeNode *&left_most, TreeNode *&right_most) {
        if (root->left == nullptr && root->right == nullptr) {
            left_most = root;
            right_most = root;
            return;
        }
        
        TreeNode *ll, *lr, *rl, *rr;
        
        if (root->left != nullptr) {
            flattenRecursive(root->left, ll, lr);
        } else {
            ll = lr = root;
        }
        if (root->right != nullptr) {
            flattenRecursive(root->right, rl, rr);
        } else {
            rl = rr = root;
        }
        
        TreeNode *ptr;
        root->left = nullptr;
        if (ll != root) {
            root->right = ll;
            lr->right = nullptr;
            ptr = lr;
        } else {
            ptr = root;
        }
        if (rr != root) {
            ptr->right = rl;
        }
        
        left_most = root;
        if (rr != root) {
            right_most = rr;
        } else {
            right_most = lr;
        }
    }
};