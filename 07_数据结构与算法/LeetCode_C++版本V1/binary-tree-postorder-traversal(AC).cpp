// 1AC, the trivial recursive version.
class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        result.clear();
		
		if(root == nullptr){
			return result;
		}
		
		preorderTraversalRecursive(root);
		
        return result;
    }
private:
    void preorderTraversalRecursive(TreeNode *root) {
        if(root == nullptr){
            return;
        }
        preorderTraversalRecursive(root->left);
        preorderTraversalRecursive(root->right);
        result.push_back(root->val);
    }
    vector<int> result;
};