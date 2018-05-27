class Solution {
public:
    ListNode *insertionSortList(ListNode *head) {
        if(nullptr == head){
            return head;
        }
        ListNode *ptr, *root;
        ListNode *p1, *p2;
        
        root = head;
		head = head->next;
		root->next = nullptr;
        while(head != nullptr){
			p1 = head->next;
			ptr = root;
			if(head->val <= root->val){
				head->next = root;
				root = head;
			}else{
				while(ptr->next != nullptr){
					if(head->val >= ptr->val && head->val <= ptr->next->val){
						break;
					}else{
						ptr = ptr->next;
					}
				}
				p2 = ptr->next;
				ptr->next = head;
				head->next = p2;
			}
			head = p1;
        }
        
		// 1WA here, not head = root->next;
        head = root;
        return head;
    }
};