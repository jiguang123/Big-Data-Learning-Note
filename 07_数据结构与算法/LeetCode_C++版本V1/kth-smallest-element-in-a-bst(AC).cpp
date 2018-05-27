// 1CE, 1AC, recursive solution
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        int cc = 0;
        int val;
        search(root, cc, k, val);
        return val;
    }
private:
    void search(TreeNode *root, int &cc, int k, int &val) {
        if (root == NULL) {
            return;
        }
        search(root->left, cc, k, val);
        if (cc == k) {
            return;
        }
        ++cc;
        if (cc == k) {
            val = root->val;
            return;
        }
        search(root->right, cc, k, val);
    }
};