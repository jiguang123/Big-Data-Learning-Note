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
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if(head == nullptr){
			// 1CE here, supposed to be nullptr, wrote 'null'
            return nullptr;
        }
        
        if(head->next == nullptr){
            delete head;
            return nullptr;
        }
        
        ListNode *p1, *p2;
        int i;
        
        p1 = head;
        while(true){
            p2 = p1;
            for(i = 0; i < n; ++i){
                if(p2 == nullptr){
                    break;
                }
                p2 = p2->next;
            }
            if(i < n){
                // abnormal case, invalid n
                // possibly n is too large
                return head;
            }
            if(p2 == nullptr){
                break;
            }else{
				// 1TLE here, didn't move p1 forward
                p1 = p1->next;
            }
        }
        // p1 is the node to be removed
        p2 = p1->next;
        while(p2 != nullptr){
            p1->val = p2->val;
            p1 = p1->next;
            p2 = p1->next;
        }
        
        p2 = head;
        while(p2->next->next != nullptr){
            p2 = p2->next;
        }
		// 1RE here, sentence mistakenly put in the while loop.. silly~
        delete p2->next;
        p2->next = nullptr;
        
        return head;
    }
};