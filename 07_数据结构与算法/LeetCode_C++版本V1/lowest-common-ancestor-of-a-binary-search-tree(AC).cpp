// 1WA, 1AC, be cautious
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
typedef long long int LL;
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!(root && p && q)) {
            return NULL;
        }
        while (sign(0LL + p->val - root->val) * sign(0LL + q->val - root->val) > 0) {
            root = p->val < root->val ? root->left : root->right;
        }
        return root;
    }
private:
    int sign(LL x) {
        return x > 0 ? +1 : x < 0 ? -1 : 0;
    }
};