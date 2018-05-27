// 2WA, 1AC, should've think more before starting coding
class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        result.clear();
		
		if(root == nullptr){
			return result;
		}
		
		vstack.clear();
		cstack.clear();
		vstack.push_back(root);
		cstack.push_back(0);
		while(vstack.size() > 0){
		    if(cstack[cstack.size() - 1] == 0){
	            ++cstack[cstack.size() - 1];
		        if(vstack[vstack.size() - 1]->left != nullptr){
		            cstack.push_back(0);
		            vstack.push_back(vstack[vstack.size() - 1]->left);
		        }
		    }else if(cstack[cstack.size() - 1] == 1){
		        ++cstack[cstack.size() - 1];
		        if(vstack[vstack.size() - 1]->right != nullptr){
		            cstack.push_back(0);
					vstack.push_back(vstack[vstack.size() - 1]->right);
					// 1WA here, cannot push result here
					// result.push_back(vstack[vstack.size() - 1]->val);
		            // 1WA here, cannot replace node here, this works for preorder, but not postorder
					// vstack[vstack.size() - 1] = vstack[vstack.size() - 1]->right;
		        }
		    }else{
				result.push_back(vstack[vstack.size() - 1]->val);
		        cstack.pop_back();
		        vstack.pop_back();
		    }
		}
		
        return result;
    }
private:
    vector<int> result;
	vector<TreeNode *> vstack;
	vector<int> cstack;
};