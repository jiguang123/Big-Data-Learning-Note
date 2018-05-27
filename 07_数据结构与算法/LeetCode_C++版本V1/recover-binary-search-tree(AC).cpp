// 2CE, 2WA, 1AC
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
    void recoverTree(TreeNode *root) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        
        // 1CE here, incomplete sentence
        if(root == nullptr){
            return;
        }
        
        v1 = p1 = nullptr;
        v2 = p2 = nullptr;
        f1 = false;
        
        inorder(root);
        
        if(p1 == nullptr || p2 == nullptr){
            return;
        }
        
        int tmp;
        tmp = p1->val;
        p1->val = p2->val;
        p2->val = tmp;
    }
private:
    bool f1;
    TreeNode *v1, *v2;
    // 1CE here, comma missing
    TreeNode *p1, *p2;
    
    void inorder(TreeNode *root) {
        if(root == nullptr){
            return;
        }
        
        inorder(root->left);
        v1 = v2;
        v2 = root;
        if(f1){
            if(v1 != nullptr && v2 != nullptr){
                if(v1->val > v2->val){
                    p2 = v2;
                }
            }
        }else{
            if(v1 != nullptr && v2 != nullptr){
                if(v1->val > v2->val){
                    p1 = v1;
                    // 1WA here, should set $p2
                    p2 = v2;
                    // 1WA here, this sentence should be inside if(){}
                    f1 = true;
                }
            }
        }
        inorder(root->right);
    }
};