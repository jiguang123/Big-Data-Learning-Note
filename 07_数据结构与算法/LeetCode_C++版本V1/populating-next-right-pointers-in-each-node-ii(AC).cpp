// 1WA, 1AC, the first attempt is wrong, only works for perfect binary trees
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if(root == nullptr){
            return;
        }
        
        TreeLinkNode *pp;
        
        // search the next pointer from left to right
        pp = root->next;
        while(pp != nullptr){
            if(pp->left != nullptr){
                pp = pp->left;
                break;
            }
            if(pp->right != nullptr){
                pp = pp->right;
                break;
            }
            pp = pp->next;
        }
        
        if(root->right != nullptr){
            root->right->next = pp;
        }
        
        if(root->left != nullptr){
            root->left->next = (root->right != nullptr) ? root->right : pp;
        }
        
        // since the searching of next pointer is from left to right
        // the recursion must be done from right to left 
        connect(root->right);
        connect(root->left);
    }
};