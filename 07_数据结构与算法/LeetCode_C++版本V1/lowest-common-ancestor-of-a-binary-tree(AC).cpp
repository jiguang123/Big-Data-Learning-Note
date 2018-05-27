// O(n) solution with parents and depths.
#include <algorithm>
#include <unordered_map>
using namespace std;
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        parent.clear();
        depth.clear();
        
        depth[NULL] = 0;
        calcDepth(root, NULL, 1);
        int hp = depth[p];
        int hq = depth[q];
        
        if (hp > hq) {
            // For the sake of simplicity, make sure p is no deeper than q.
            swap(hp, hq);
            swap(p, q);
        }
        while (hp < hq) {
            q = parent[q];
            --hq;
        }
        while (p != q) {
            p = parent[p];
            q = parent[q];
            --hp;
            --hq;
        }
        return p;
    }
private:
    unordered_map<TreeNode *, int> depth;
    unordered_map<TreeNode *, TreeNode *> parent;
    
    void calcDepth(TreeNode *root, TreeNode *par, int h) {
        if (root == NULL) {
            return;
        }
        parent[root] = par;
        calcDepth(root->left, root, h + 1);
        calcDepth(root->right, root, h + 1);
        depth[root] = h;
    }
};