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
    bool hasCycle(ListNode *head) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
		if(head == nullptr){
			return false;
		}
		
		ListNode *p1, *p2;
		
		p1 = p2 = head;
		while(true){
			if(p1->next == nullptr){
				return false;
			}
			if(p2->next == nullptr || p2->next->next == nullptr){
				return false;
			}
			
			p1 = p1->next;
			p2 = p2->next->next;
			if(p1 == p2){
				// Same address, same node
				// There is a cycle in the list
				return true;
			}
		}
    }
};