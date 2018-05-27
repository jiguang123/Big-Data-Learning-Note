// 1WA, 1AC, very good~
// #define MY_MAIN
#include <cstdio>
#include <vector>
using namespace std;
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#ifdef MY_MAIN
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
#endif
class Solution {
public:
	vector<TreeNode *> generateTrees(int n) {
		int i;
		vector<int> num;
		vector<TreeNode *> result;
		
		result.clear();
		if (n == 0) {
			// 1WA here, you should return an empty tree when n=0.
			result.push_back(NULL);
			return result;
		}
		
		for (i = 1; i <= n; ++i) {
			num.push_back(i);
		}
		result = generateTreeRecursive(num);
		return result;
	}
private:
	vector<TreeNode *> generateTreeRecursive(vector<int> num) {
		vector<TreeNode *> res;
		TreeNode *root_ptr;
		
		res.clear();
		if (num.size() == 0) {
			res.push_back(NULL);
			return res;
		} else if (num.size() == 1) {
			root_ptr = new TreeNode(num[0]);
			res.push_back(root_ptr);
			return res;
		}
		
		vector<int> vleft, vright;
		vector<TreeNode *> res_left, res_right;
		int count_left, count_right;
		int i, j, k;
		
		for (i = 0; i < (int)num.size(); ++i) {
			vleft.clear();
			vright.clear();
			res_left.clear();
			res_right.clear();
			// the left subtree
			for (j = 0; j < i; ++j) {
				vleft.push_back(num[j]);
			}
			// the right subtree
			for (j = i + 1; j < (int)num.size(); ++j) {
				vright.push_back(num[j]);
			}
			res_left = generateTreeRecursive(vleft);
			res_right = generateTreeRecursive(vright);
			count_left = (int)res_left.size();
			count_right = (int)res_right.size();
			for (j = 0; j < count_left; ++j) {
				for (k = 0; k < count_right; ++k) {
					root_ptr = new TreeNode(num[i]);
					// root_ptr->left = copyTreeRecursive(res_left[j]);
					// root_ptr->right = copyTreeRecursive(res_right[k]);
					root_ptr->left = res_left[j];
					root_ptr->right = res_right[k];
					res.push_back(root_ptr);
				}
			}
		}
		
		return res;
	}

	TreeNode *copyTreeRecursive(const TreeNode *root)
	{
		TreeNode *new_root;
		
		if (root == NULL) {
			return NULL;
		}
		new_root = new TreeNode(root->val);
		if (root->left != NULL) {
			new_root->left = copyTreeRecursive(root->left);
		}
		if (root->right != NULL) {
			new_root->right = copyTreeRecursive(root->right);
		}

		return new_root;
	}
};

#ifdef MY_MAIN
void preorderTraversal(const TreeNode *root, vector<int> &result)
{
	if (root == NULL) {
		result.push_back(0);
	}
	result.push_back(root->val);
	if (root->left != NULL) {
		preorderTraversal(root->left, result);
	} else {
		result.push_back(0);
	}
	if (root->right != NULL) {
		preorderTraversal(root->right, result);
	} else {
		result.push_back(0);
	}
}

int main()
{
	int n;
	Solution solution;
	vector<int> traversal_result;
	vector<TreeNode *> trees;
	int i, j;
	
	while (scanf("%d", &n) == 1) {
		if (n < 0) {
			continue;
		}
		trees = solution.generateTrees(n);
		for (i = 0; i < (int)trees.size(); ++i) {
			traversal_result.clear();
			preorderTraversal(trees[i], traversal_result);
			for (j = 0; j < (int)traversal_result.size(); ++j) {
				if (j == 0) {
					printf("%d", traversal_result[j]);
				} else {
					printf(" %d", traversal_result[j]);
				}
			}
			printf("\n");
		}
		printf("Catalan[%d] = %d\n", n, (int)trees.size());
		printf("\n");
	}
	
	return 0;
}
#endif