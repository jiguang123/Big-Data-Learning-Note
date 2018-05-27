// 1AC, excellent!!!
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
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        return recoverTree(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
    }
private:
    TreeNode *recoverTree(vector<int> &preorder, vector<int> &inorder, int l1, int r1, int l2, int r2) {
        if(l1 > r1){
            return nullptr;
        }
        
        if(l2 > r2){
            return nullptr;
        }
        
        TreeNode *root = new TreeNode(preorder[l1]);
        int i;
        
        for(i = l2; i <= r2; ++i){
            if(inorder[i] == root->val){
                break;
            }
        }
        
        root->left = recoverTree(preorder, inorder, l1 + 1, (l1 + 1)  + (i - 1 - l2), l2, i - 1);
        root->right = recoverTree(preorder, inorder, r1 - (r2 - i - 1), r1, i + 1, r2);
        
        return root;
    }
};