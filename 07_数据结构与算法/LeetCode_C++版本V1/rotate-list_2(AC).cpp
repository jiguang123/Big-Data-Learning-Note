// 1AC, excellent
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
        if(nullptr == head){
            return head;
        }
        
        int len = 0;
        ListNode *p1 = nullptr, *p2 = nullptr, *tail = nullptr;
        
        // calculate the length of the list
        p1 = head;
        len = 0;
        while(p1 != nullptr){
            if(p1->next == nullptr){
                tail = p1;
            }
            ++len;
            p1 = p1->next;
        }
        if(tail == nullptr){
            // cannot possibly happen
            return nullptr;
        }
        
        // reduce k to k % len
        k = k % len;
        if(k == 0){
            return head;
        }
        
        // find the (k + 1)th node from the end
        p1 = p2 = head;
        for(int i = 0; i < k + 1; ++i){
            p1 = p1->next;
        }
        while(p1 != nullptr && p2 != nullptr){
            p1 = p1->next;
            p2 = p2->next;
        }
        
        p1 = head;
        head = p2->next;
        p2->next = nullptr;
        tail->next = p1;
        return head;
    }
};