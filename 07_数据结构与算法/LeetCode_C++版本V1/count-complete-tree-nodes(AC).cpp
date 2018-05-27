// 1RE, 1WA, 1AC, NULL
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
    int countNodes(TreeNode* root) {
		if (root == NULL) {
			return 0;
		}
		
		int h = 0;
		TreeNode *p = root;
		while (p->left != NULL) {
			p = p->left;
			++h;
		}
		int ll = 0;
		int rr = (1 << h) - 1;
		
		if (hasNode(root, rr, h)) {
			return (1 << h + 1) - 1;
		}
		
		int mm;
		while (rr - ll > 1) {
			mm = ll + rr >> 1;
			if (hasNode(root, mm, h)) {
				ll = mm;
			} else {
				rr = mm;
			}
		}
		return (1 << h) + ll;
    }
private:
	bool hasNode(TreeNode *root, int x, int h) {
		TreeNode *p;
		int i;
		
		p = root;
		for (i = h - 1; i >= 0; --i) {
			if (x & (1 << i)) {
				p = p->right;
			} else {
				p = p->left;
			}
		}
		return p != NULL;
	}
};