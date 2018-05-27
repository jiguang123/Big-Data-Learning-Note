// 1RE, 1AC
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
    vector<vector<int>> pathSum(TreeNode *root, int sum) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int i, n;
        n = result.size();
        for(i = 0; i < n; ++i){
            result[i].clear();
        }
        result.clear();
        arr.clear();
        if(root == nullptr){
            return result;
        }
        // 1RE here, forgot to push into $arr
        arr.push_back(root->val);
        dfs(root, root->val, sum);
        arr.pop_back();
        
        return result;
    }
private:
    vector<vector<int>> result;
    vector<int> arr;
    
    void dfs(TreeNode *root, int sum, int target){
        if(root == nullptr){
            return;
        }
        
        if(root->left == nullptr && root->right == nullptr){
            if(sum == target){
                result.push_back(arr);
            }
            return;
        }
        
        if(root->left != nullptr){
            arr.push_back(root->left->val);
            dfs(root->left, sum + root->left->val, target);
            arr.pop_back();
        }
        if(root->right != nullptr){
            arr.push_back(root->right->val);
            dfs(root->right, sum + root->right->val, target);
            arr.pop_back();
        }
    }
};