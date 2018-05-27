// 1WA, 1CE, 1AC
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
    bool isValidBST(TreeNode *root) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if(root == nullptr){
            return true;
        }
        arr.clear();
        // 1WA here, the in-order traversal of BST is sorted.
        inorderTraversal(root);
        
        int i, n;
        
        n = arr.size();
        for(i = 0; i < n - 1; ++i){
            if(arr[i] >= arr[i + 1]){
                break;
            }
        }
        arr.clear();
        
        return (i == n - 1);
    }
private:
    vector<int> arr;
    
    void inorderTraversal(TreeNode *root) {
        // 1CE, null or nullptr...
        if(root == nullptr){
            return;
        }
        
        if(root->left != nullptr){
            inorderTraversal(root->left);
        }
        arr.push_back(root->val);
        if(root->right != nullptr){
            inorderTraversal(root->right);
        }
    }
};