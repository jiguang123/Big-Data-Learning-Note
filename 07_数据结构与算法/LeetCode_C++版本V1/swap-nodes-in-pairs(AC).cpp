// This problem is tricky, 3WA
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
    ListNode *swapPairs(ListNode *head) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        ListNode *p1 = nullptr, *p2 = nullptr;
		
		if(head == nullptr){
			return head;
		}
		
		p1 = head;
		p2 = head->next;
		if(p2 == nullptr){
			return p1;
		}
		
		bool first_swap = true;
		ListNode *tmp, *par;
		ListNode *root;
		
		par = new ListNode(0);
		root = par;
		par->next = p1;
		while(true){
			p1->next = p2->next;
			p2->next = p1;
			
			tmp = p1;
			p1 = p2;
			p2 = tmp;
			
			par->next = p1;
			par = p2;
			
			if(first_swap){
				head = p1;
				first_swap = false;
			}
			
			p1 = p1->next;
			p2 = p1->next;
			if(p2 == nullptr){
				break;
			}
			
			p1 = p1->next;
			p2 = p1->next;
			if(p2 == nullptr){
				break;
			}
		}
		
		delete root;
		root = nullptr;
		return head;
    }
};