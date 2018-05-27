// 2TLE, 1WA, 1AC
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
    ListNode *rotateRight(ListNode *head, int k) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if(head == nullptr){
            return head;
        }
        
        int i, len;
        ListNode *tail;
        ListNode *newhead;
        ListNode *ptr1, *ptr2;
        
        len = 0;
        ptr1 = head;
        while(ptr1 != nullptr){
            ptr1 = ptr1->next;
            ++len;
        }
        k = k % len;
        if(k == 0){
            return head;
        }
        
        tail = head;
        while(tail->next != nullptr){
            tail = tail->next;
        }
        // Make it a loop~
        tail->next = head;
        
        ptr1 = head;
        while(true){
            ptr2 = ptr1;
            for(i = 0; i <= k; ++i){
                ptr2 = ptr2->next;
            }
            if(ptr2 == head){
                // 1WA here, should be $ptr1, wrote $ptr2
                newhead = ptr1->next;
                ptr1->next = nullptr;
                break;
            }else{
                // 2TLE here, forgot to move $ptr1 forward
                ptr1 = ptr1->next;
            }
        }
        
        return newhead;
    }
};