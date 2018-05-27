// 1AC, excellent.
class Solution {
public:
    vector<int> preorderTraversal(TreeNode *root) {
        result.clear();
		
		if(root == nullptr){
			return result;
		}
		
		vstack.clear();
		cstack.clear();
		vstack.push_back(root);
		cstack.push_back(0);
		result.push_back(root->val);
		while(vstack.size() > 0){
		    if(cstack[cstack.size() - 1] == 0){
	            ++cstack[cstack.size() - 1];
		        if(vstack[vstack.size() - 1]->left != nullptr){
		            cstack.push_back(0);
		            vstack.push_back(vstack[vstack.size() - 1]->left);
		            result.push_back(vstack[vstack.size() - 1]->val);
		        }
		    }else if(cstack[cstack.size() - 1] == 1){
		        ++cstack[cstack.size() - 1];
		        if(vstack[vstack.size() - 1]->right != nullptr){
		            cstack[cstack.size() - 1] = 0;
		            vstack[vstack.size() - 1] = vstack[vstack.size() - 1]->right;
		            result.push_back(vstack[vstack.size() - 1]->val);
		        }
		    }else{
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