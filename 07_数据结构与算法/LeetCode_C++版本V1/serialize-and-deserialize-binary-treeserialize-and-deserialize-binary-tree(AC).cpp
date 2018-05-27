#include <string>
#include <vector>
using namespace std;
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        vector<string> v;
        preorderSerialize(root, v);
        string data = v[0];
        int n = v.size();
        int i, j;
        for (i = 1; i < n; ++i) {
            data.push_back(STOP_CHAR);
            for (j = 0; j < v[i].length(); ++j) {
                data.push_back(v[i][j]);
            }
        }
        return data;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<string> v;
        tokenize(data, v);
        int n = v.size();
        int idx = 0;
        return preorderDeserialize(v, idx);
    }
private:
    static const char STOP_CHAR = ',';
    
    void tokenize(const string &s, vector<string> &v) {
        int i, j;
        int n = s.length();
        string tk;
        
        i = 0;
        while (true) {
            while (i < n && s[i] != STOP_CHAR) {
                tk.push_back(s[i++]);
            }
            v.push_back(tk);
            tk.clear();
            if (i >= n) {
                break;
            }
            while (i < n && s[i] == STOP_CHAR) {
                ++i;
            }
        }
    }
    
    TreeNode *preorderDeserialize(const vector<string> &v, int &idx) {
        if (v[idx] == "#") {
            ++idx;
            return NULL;
        }
        int val;
        sscanf(v[idx].data(), "%d", &val);
        TreeNode *root = new TreeNode(val);
        ++idx;
        
        root->left = preorderDeserialize(v, idx);
        root->right = preorderDeserialize(v, idx);
        return root;
    }
    
    void preorderSerialize(const TreeNode *root, vector<string> &v) {
        if (root == NULL) {
            v.push_back("#");
            return;
        }
        v.push_back(to_string(root->val));
        preorderSerialize(root->left, v);
        preorderSerialize(root->right, v);
    }
};