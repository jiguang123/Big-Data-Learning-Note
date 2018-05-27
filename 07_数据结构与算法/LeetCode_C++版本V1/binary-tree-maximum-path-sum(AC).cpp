// 1WA, 1AC, recursive solution in O(n) time.
#include <algorithm>
#include <climits>
using namespace std;

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
    int maxPathSum(TreeNode *root) {
        max_val = INT_MIN;
        maxPathSumRecursive(root);
        
        return max_val;
    }
private:
    int max_val;
    
    // return the maximum root-to-leaf sum, the 'root' refers to the current node as the root.
    int maxPathSumRecursive(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }
        // the root-to-leaf sum
        int sum_single;
        // the leaf-to-leaf or root-to-leaf sum
        int sum_double;
        int max1 = 0, max2 = 0;
        
        sum_double = sum_single = root->val;
        if (root->left != nullptr) {
            max1 = maxPathSumRecursive(root->left);
            if (max1 < 0) {
                max1 = 0;
            }
        }
        if (root->right != nullptr) {
            max2 = maxPathSumRecursive(root->right);
            if (max2 < 0) {
                max2 = 0;
            }
        }
        sum_single += max(max1, max2);
        sum_double += max1 + max2;
        if (sum_double > max_val) {
            max_val = sum_double;
        }
        
        return sum_single;
    }
};