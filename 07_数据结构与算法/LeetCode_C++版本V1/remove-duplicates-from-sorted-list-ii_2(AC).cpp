// 1RE, 1AC, could've been perfect with more patience.
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
        if(head == nullptr){
            return head;
        }
		
		int tmp_val = 0;
		ListNode *par = nullptr, *ptr = nullptr;
		// remove all head duplicates first
		// 1RE here, {1} would result in $par uninitialized.
		par = head;
		while(head != nullptr && head->next != nullptr){
			if(head->val == head->next->val){
				// head node has duplicates
				tmp_val = head->val;
				while(head != nullptr && head->val == tmp_val){
					ptr = head;
					head = head->next;
					delete ptr;
				}
			}else{
				par = head;
				break;
			}
		}
		
		ListNode *ptr2 = nullptr;
		ptr = par->next;
		while(ptr != nullptr && ptr->next != nullptr){
			if(ptr->val == ptr->next->val){
				tmp_val = ptr->val;
				while(ptr != nullptr && ptr->val == tmp_val){
					ptr2 = ptr;
					ptr = ptr->next;
					delete ptr2;
				}
				par->next = ptr;
			}else{
				par = ptr;
				ptr = ptr->next;
			}
		}
        
        return head;
    }
};