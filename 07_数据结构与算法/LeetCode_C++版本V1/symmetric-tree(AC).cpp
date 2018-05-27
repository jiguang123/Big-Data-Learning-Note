//#define __MAIN__

#ifdef __MAIN__
#include <cstdio>
#include <cstdlib>
using namespace std;
#endif

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#ifdef __MAIN__
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
#endif

class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
		if(root == nullptr){
			return true;
		}
		return isMirror(root->left, root->right);
    }
private:
	bool isMirror(TreeNode *ra, TreeNode *rb) {
		if(ra == nullptr && rb == nullptr){
			return true;
		}
		
		if(ra == nullptr || rb == nullptr){
			return false;
		}

		if(ra->val == rb->val){
			return isMirror(ra->left, rb->right) && isMirror(ra->right, rb->left);
		}else{
			return false;
		}
	}
};