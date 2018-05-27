// 1CE, 1AC, excellent.
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
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
    TreeNode *sortedListToBST(ListNode *head) {
        if (head == nullptr) {
            return nullptr;
        }
        int n = 0;
        ListNode *ptr = head;
        while (ptr !=  nullptr) {
            ptr = ptr->next;
            ++n;
        }
        
        if (n == 1) {
            return new TreeNode(head->val);
        }
        
        int nl, nr;
        int i;
        ListNode *head1, *root, *head2;
        
        nr = (n - 1) / 2;
        nl = n - 1 - nr;
        // nl must be positive
        // nr could be 0
        ptr = head;
        for (i = 0; i < nl - 1; ++i) {
            ptr = ptr->next;
        }
        head1 = head;
        root = ptr->next;
        ptr->next = nullptr;
        head2 = root->next;
        root->next = nullptr;
        
        TreeNode *tree_root = nullptr;
        
        tree_root = new TreeNode(root->val);
        tree_root->left = sortedListToBST(head1);
        tree_root->right = sortedListToBST(head2);
        
        return tree_root;
    }
};