// 2WA, 1RE, 1AC, not so easy..
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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
		
		if(l1 == nullptr || l2 == nullptr){
			return nullptr;
		}
		
		ListNode *head;
		ListNode *ptr, *p1, *p2;
		bool first;
		ListNode *par1, *par2, *par;
		ListNode *r1, *r2, *rr;
		int carry;
		
		p1 = l1;
		p2 = l2;
		
		carry = 0;
		
		r1 = par1 = new ListNode(0);
		r2 = par2 = new ListNode(0);
		rr = par = new ListNode(0);
		
		par1->next = l1;
		par2->next = l2;
		par->next = nullptr;
		
		first = true;
		//while(p1 != nullptr && p2 != nullptr){
		// 1WA here, {1,8}, {0}
		while(p1 != nullptr || p2 != nullptr){
			ptr = new ListNode(0);
			if(p1 != nullptr){
				ptr->val += p1->val;
			}
			if(p2 != nullptr){
				ptr->val += p2->val;
			}
			/*
			1WA here, wrong if statement
			if(p1 != nullptr){
				ptr->val += carry;
			}
			*/
			ptr->val += carry;

			par->next = ptr;
			par = par->next;
			if(p1 != nullptr){
				par1 = par1->next;
			}
			if(p2 != nullptr){
				par2 = par2->next;
			}

			if(first){
				head = ptr;
				first = false;
			}
			
			if(ptr->val >= 10){
				ptr->val -= 10;
				carry = 1;
			}else{
				carry = 0;
			}
			
			if(p1 != nullptr){
				p1 = p1->next;
			}
			if(p2 != nullptr){
				p2 = p2->next;
			}
			ptr = ptr->next;
		}
		if(carry){
			ptr = new ListNode(1);
			par->next = ptr;
		}
		
		// 1RE here, parent pointer moved, must have an extra pointer to record the parent node on the front
		delete r1;
		delete r2;
		delete rr;
		
		return head;
    }
};