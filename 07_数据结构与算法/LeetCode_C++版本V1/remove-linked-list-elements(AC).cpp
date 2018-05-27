// 1AC, no surprise
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
	ListNode* removeElements(ListNode* head, int val) {
		ListNode *ptr;
		
		while (head != NULL && head->val == val) {
			ptr = head;
			head = head->next;
			delete ptr;
		}
		
		ListNode *head0 = head;
		
		if (head0 == NULL) {
			return NULL;
		}
		
		while (head->next != NULL) {
			if (head->next->val == val) {
				ptr = head->next;
				head->next = ptr->next;
				delete ptr;
			} else {
				head = head->next;
			}
		}
		
		return head0;
	}
};