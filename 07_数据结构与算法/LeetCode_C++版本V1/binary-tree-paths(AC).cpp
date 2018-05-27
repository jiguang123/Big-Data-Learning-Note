#include <string>
#include <stringstream>
#include <vector>
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
    vector<string> binaryTreePaths(TreeNode *root) {
        vector<string> v;
        if (root == NULL) {
            return v;
        }
        
        vector<int> path;
        
        path.push_back(root->val);
        DFS(root, v, path);
        path.pop_back();
        
        return v;
    }
private:
    void DFS(TreeNode *root, vector<string> &v, vector<int> &path) {
        if (root->left == NULL && root->right == NULL) {
            string ps = to_string(path[0]);
            
            int i;
            int n = path.size();
            for (i = 1; i < n; ++i) {
                ps += "->" + to_string(path[i]);
            }
            v.push_back(ps);
            
            return;
        }
        if (root->left != NULL) {
            path.push_back(root->left->val);
            DFS(root->left, v, path);
            path.pop_back();
        }
        if (root->right != NULL) {
            path.push_back(root->right->val);
            DFS(root->right, v, path);
            path.pop_back();
        }
    }
};