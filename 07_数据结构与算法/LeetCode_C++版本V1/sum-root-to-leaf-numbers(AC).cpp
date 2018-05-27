//1CE, 2WA, 1AC
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
    int sumNumbers(TreeNode *root) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        
        if(root == nullptr){
            return 0;
        }
        
        result = 0;
        traverse(root, root->val);
        
        return result;
    }
private:
    int result;
    void traverse(TreeNode *root, int weight) {
        // Which level should 'weight' represent, vague...
        // That's why you got two WAs here!!!
        if(root == nullptr){
            return;
        }
        
        if(root->left == nullptr && root->right == nullptr){
            result += weight;
            return;
        }
        
        if(root->left != nullptr){
            traverse(root->left, weight * 10 + root->left->val);
        }
        if(root->right != nullptr){
            traverse(root->right, weight * 10 + root->right->val);
        }
    }
};