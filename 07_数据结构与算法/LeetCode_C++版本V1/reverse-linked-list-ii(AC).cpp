// 3RE, 1WA, 1AC, so difficult...
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int i;
        ListNode *p1, *p2;
        ListNode *root, *t1, *t2;
        ListNode *par;
        
        root = new ListNode(0);
        root->next = head;
        p1 = root;
        for(i = 0; i < m - 1; ++i){
            p1 = p1->next;
        }
		// 1RE here, wrong pointer
        par = p1;
        p1 = p1->next;
        
        t1 = nullptr;
        t2 = p1;
		// 1RE here, i < n - m + 1
        for(i = 0; i < n - m + 1; ++i){
            p2 = t2;
            p2 = p2->next;
            t2->next = t1;
            t1 = t2;
			// 1RE here, wrong pointer
            t2 = p2;
        }
		// 1WA, wrong pointer
        par->next = t1;
        p1->next = t2;
        head = root->next;
        
        delete root;
        return head;
    }
};