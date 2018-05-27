// 1AC, count the number of nodes and align them
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *p1, *p2;
        int n1, n2;
        
        p1 = headA;
        n1 = 0;
        while (p1 != nullptr) {
            ++n1;
            p1 = p1->next;
        }
        
        p2 = headB;
        n2 = 0;
        while (p2 != nullptr) {
            ++n2;
            p2 = p2->next;
        }
        
        p1 = headA;
        p2 = headB;
        
        int i;
        if (n1 < n2) {
            for (i = 0; i < n2 - n1; ++i) {
                p2 = p2->next;
            }
        } else if (n1 > n2) {
            for (i = 0; i < n1 - n2; ++i) {
                p1 = p1->next;
            }
        }
        
        while (p1 != nullptr && p2 != nullptr && p1 != p2) {
            p1 = p1->next;
            p2 = p2->next;
        }
        
        return p1;
    }
};