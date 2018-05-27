// 1AC, incredibly smooth, keep it coming~
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
    ListNode *sortList(ListNode *head) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if(head == nullptr || head->next == nullptr){
            return head;
        }
        
        int i, len;
        ListNode *ptr;
        
        ptr = head;
        len = 0;
        while(ptr != nullptr){
            ptr = ptr->next;
            ++len;
        }
        
        ListNode *h1, *h2;
        ptr = head;
        for(i = 0; i < len / 2 - 1; ++i){
            ptr = ptr->next;
        }
        h1 = head;
        h2 = ptr->next;
        ptr->next = nullptr;
        
        h1 = sortList(h1);
        h2 = sortList(h2);
        head = mergeList(h1, h2);
        
        return head;
    }
private:
    ListNode *mergeList(ListNode *head1, ListNode *head2) {
        if(head1 == nullptr){
            return head2;
        }else if(head2 == nullptr){
            return head1;
        }
        
        ListNode *head = nullptr;
        ListNode *ptr = nullptr;
        
        while(head1 != nullptr && head2 != nullptr){
            if(head1->val < head2->val){
                if(ptr == nullptr){
                    ptr = head1;
                    head1 = head1->next;
                    ptr->next = nullptr;
                    head = ptr;
                }else{
                    ptr->next = head1;
                    head1 = head1->next;
                    ptr = ptr->next;
                    ptr->next = nullptr;
                }
            }else{
                if(ptr == nullptr){
                    ptr = head2;
                    head2 = head2->next;
                    ptr->next = nullptr;
                    head = ptr;
                }else{
                    ptr->next = head2;
                    head2 = head2->next;
                    ptr = ptr->next;
                    ptr->next = nullptr;
                }
            }
        }
        while(head1 != nullptr){
            if(ptr == nullptr){
                ptr = head1;
                head1 = head1->next;
                ptr->next = nullptr;
                head = ptr;
            }else{
                ptr->next = head1;
                head1 = head1->next;
                ptr = ptr->next;
                ptr->next = nullptr;
            }
        }
        while(head2 != nullptr){
            if(ptr == nullptr){
                ptr = head2;
                head2 = head2->next;
                ptr->next = nullptr;
                head = ptr;
            }else{
                ptr->next = head2;
                head2 = head2->next;
                ptr = ptr->next;
                ptr->next = nullptr;
            }
        }
        
        return head;
    }
};