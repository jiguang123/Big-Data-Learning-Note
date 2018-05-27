// 1AC, easy
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head == NULL) {
            return NULL;
        }
        
        int len = 0;
        ListNode *p = head;
        while (p != NULL) {
            p = p->next;
            ++len;
        }
        if (len == n) {
            p = head;
            head = head->next;
            delete p;
            return head;
        }
        
        p = head;
        int i;
        for (i = 0; i < len - n - 1; ++i) {
            p = p->next;
        }
        ListNode *q = p->next;
        p->next = q->next;
        delete q;
        
        return head;
    }
};