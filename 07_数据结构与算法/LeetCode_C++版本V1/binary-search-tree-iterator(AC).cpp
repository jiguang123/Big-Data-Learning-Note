// 1CE, 1MLE, 1WA, 1AC, anonther good problem
#include <unordered_map>
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
class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        nn.clear();
        currentNode = nullptr;
        
        if (root == nullptr) {
            return;
        }
        
        TreeNode *ll, *rr;
        findSuccessor(root, ll, rr);
        currentNode = ll;
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return currentNode != nullptr;
    }

    /** @return the next smallest number */
    int next() {
        int val = currentNode->val;
        currentNode = nn[currentNode];
        return val;
    }
    
    ~BSTIterator() {
        nn.clear();
    }
private:
    unordered_map<TreeNode *, TreeNode *> nn;
    TreeNode *currentNode;
    
    void findSuccessor(TreeNode *root, TreeNode *&left, TreeNode *&right) {
        TreeNode *ll, *lr, *rl, *rr;
        
        if (root->left == nullptr) {
            ll = root;
            lr = root;
        } else {
            findSuccessor(root->left, ll, lr);
            nn[lr] = root;
        }
        
        if (root->right == nullptr) {
            rl = root;
            rr = root;
        } else {
            findSuccessor(root->right, rl, rr);
            nn[root] = rl;
        }
        left = ll;
        right = rr;
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */