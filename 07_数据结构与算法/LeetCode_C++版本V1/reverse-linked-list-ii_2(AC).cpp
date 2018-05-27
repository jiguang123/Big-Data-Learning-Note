// 1WA, 1AC, faulty operator is extremely difficult to debug, take this lesson!
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
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int i;
        ListNode *p1, *p2;
        ListNode *t1, *t2;
        ListNode *par;
        
		// 1WA here, (O_o), != or ==? ...
		if(head == nullptr){
			return head;
		}
		
		if(m > 1){
			p1 = head;
			for(i = 0; i < m - 2; ++i){
				p1 = p1->next;
			}
			par = p1;
			p1 = p1->next;
		}else{
			par = nullptr;
			p1 = head;
		}
        
        t1 = nullptr;
        t2 = p1;
        for(i = 0; i < n - m + 1; ++i){
            p2 = t2->next;
            t2->next = t1;
            t1 = t2;
            t2 = p2;
        }
		if(par != nullptr){
			par->next = t1;
		}else{
			head = t1;
		}
		p1->next = t2;
        
        return head;
    }
};