// 2RE, 1AC, always keep an eye out for nullptr!
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
    ListNode *partition(ListNode *head, int x) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        ListNode *l1 = nullptr, *l2 = nullptr;
		ListNode *h1 = nullptr, *h2 = nullptr;
        
        while(head != nullptr){
            if(head->val < x){
				if(h1 == nullptr){
					h1 = l1 = head;
				}else{
					l1->next = head;
					l1 = l1->next;
				}
                head = head->next;
                l1->next = nullptr;
            }else{
				if(h2 == nullptr){
					h2 = l2 = head;
				}else{
					l2->next = head;
					l2 = l2->next;
				}
                head = head->next;
                l2->next = nullptr;
            }
        }
        // 2RE here, note that h1 and h2 may be empty!
        if(h1 == nullptr){
            return h2;
        }else if(h2 == nullptr){
            return h1;
        }
        l1->next = h2;
        head = h1;
		
        return head;
    }
};