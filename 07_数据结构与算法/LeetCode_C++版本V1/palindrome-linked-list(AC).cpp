// 1AC, Yes!
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
    bool isPalindrome(ListNode* head) {
        if (head == NULL) {
            return true;
        }
        
        ListNode *p1, *p2;
        p1 = p2 = head;
        while (true) {
            p2 = p2->next;
            if (p2 == NULL) {
                break;
            }
            p2 = p2->next;
            if (p2 == NULL) {
                break;
            }
            p1 = p1->next;
        }
        
        ListNode *h1, *h2;
        ListNode *t1;
        // Cut the list in half
        h1 = head;
        h2 = p1->next;
        t1 = p1;
        t1->next = NULL;
        
        // Check for palindrome
        h2 = reverseList(h2);
        p1 = h1;
        p2 = h2;
        while (p2 != NULL) {
            if (p1->val != p2->val) {
                break;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        bool ans = p2 == NULL;
        // Restore the list
        h2 = reverseList(h2);
        t1->next = h2;
        return ans;
    }
private:
    ListNode *reverseList(ListNode *h) {
        if (h == NULL) {
            return NULL;
        }
        ListNode *p = h, *q;
        h = h->next;
        p->next = NULL;
        while (h != NULL) {
            q = h;
            h = h->next;
            q->next = p;
            p = q;
        }
        return p;
    }
};