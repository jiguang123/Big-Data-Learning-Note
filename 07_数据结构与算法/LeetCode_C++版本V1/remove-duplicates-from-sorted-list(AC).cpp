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
        // Note: The Solution object is instantiated only once and is reused by each test case.
		if(head == nullptr){
			return head;
		}
		
		ListNode *ptr1, *ptr2;

		ptr1 = head;
		ptr2 = head->next;
		while(ptr2 != nullptr){
			if(ptr1->val == ptr2->val){
				ptr1->next = ptr2->next;
				delete ptr2;
				ptr2 = ptr1->next;
			}else{
				ptr1 = ptr1->next;
				ptr2 = ptr1->next;
			}
		}

		return head;
    }
};