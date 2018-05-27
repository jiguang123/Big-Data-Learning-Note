// 1AC, nice
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
		
		// This algorithm won't work if the tree is not perfect.
		if(root->left){
			TreeLinkNode *ll, *rr;
			
			ll = root->left;
			rr = root->right;
			while(ll != nullptr){
				ll->next = rr;
				ll = ll->right;
				rr = rr->left;
			}
		}
		connect(root->left);
		connect(root->right);
    }
};