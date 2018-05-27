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
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
		if(l1 == nullptr){
			return l2;
		}else if(l2 == nullptr){
			return l1;
		}
		
		ListNode *l3, *head;
		
		if(l1->val <= l2->val){
			l3 = l1;
			l1 = l1->next;
		}else{
			l3 = l2;
			l2 = l2->next;
		}
		l3->next = nullptr;
		head = l3;
		
		while(l1 != nullptr && l2 != nullptr){
			if(l1->val <= l2->val){
				l3->next = l1;
				l1 = l1->next;
			}else{
				l3->next = l2;
				l2 = l2->next;
			}
			l3 = l3->next;
			l3->next = nullptr;
		}
		
		while(l1 != nullptr){
			l3->next = l1;
			l1 = l1->next;
			l3 = l3->next;
			l3->next = nullptr;
		}
		while(l2 != nullptr){
			l3->next = l2;
			l2 = l2->next;
			l3 = l3->next;
			l3->next = nullptr;
		}
		
		return head;
    }
};