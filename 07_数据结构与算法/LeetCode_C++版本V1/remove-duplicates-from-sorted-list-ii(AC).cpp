// 1WA, 1AC, I thought there would be more mistakes... excellent
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
    ListNode *deleteDuplicates(ListNode *head) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        bool dup;
        
        if(head == nullptr){
            return head;
        }
        
        ListNode *root;
        
        root = new ListNode(0);
        root->next = head;
        ListNode *ptr = head;
        ListNode *tmp;
        ListNode *par = root;
        
        // 1WA here, initialization for $dup missing
        dup = false;
        while(ptr != nullptr){
            if(ptr->next != nullptr){
                if(ptr->val == ptr->next->val){
                    if(!dup){
                        dup = true;
                    }
                    tmp = ptr->next;
                    ptr->next = tmp->next;
                    delete tmp;
                }else{
                    if(dup){
                        par->next = ptr->next;
                        delete ptr;
                        ptr = par->next;
                        dup = false;
                    }else{
                        par = par->next;
                        ptr = par->next;
                    }
                }
            }else{
                if(dup){
                    par->next = ptr->next;
                    delete ptr;
                    ptr = par->next;
                    dup = false;
                }else{
                    par = par->next;
                    ptr = par->next;
                }
            }
        }
        
        head = root->next;
        delete root;
        
        return head;
    }
};