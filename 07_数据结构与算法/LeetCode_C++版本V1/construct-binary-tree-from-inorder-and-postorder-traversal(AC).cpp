// 1CE, 1AC, good~
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
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        return recoverTree(inorder, postorder, 0, inorder.size() - 1, 0, postorder.size() - 1);
    }
private:
    TreeNode *recoverTree(vector<int> &inorder, vector<int> &postorder, int l1, int r1, int l2, int r2) {
        if(l1 > r1){
            return nullptr;
        }
        
        if(l2 > r2){
            return nullptr;
        }
        
        TreeNode *root = new TreeNode(postorder[r2]);
        int i;
        
        for(i = l1; i <= r1; ++i){
            if(inorder[i] == root->val){
                break;
            }
        }
        
        root->left = recoverTree(inorder, postorder, l1, i - 1, l2, l2 + (i - 1 - l1));
        // 1CE here, £¬ error
        root->right = recoverTree(inorder, postorder, i + 1, r1, r2 - 1 - (r1 - i - 1), r2 - 1);
        
        return root;
    }
};