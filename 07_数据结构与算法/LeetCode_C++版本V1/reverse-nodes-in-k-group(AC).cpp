// 1RE, 1AC, good.
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
	ListNode *reverseKGroup(ListNode *head, int k) {
		if (head == nullptr || k < 2) {
			// no change at all
			return head;
		}
		ListNode *bh, *h, *t, *at;
		
		bh = nullptr;
		h = head;
		int i;
		while (true) {
			if (h == nullptr) {
				break;
			}
			t = h;
			for (i = 1; i < k; ++i) {
				t = t->next;
				if (t == nullptr) {
					break;
				}
			}
			if (i == k) {
				at = t->next;
				t->next = nullptr;
				reverseList(h, t);
				if (bh != nullptr) {
					// put the segment in place again
					bh->next = h;
					t->next = at;
				} else {
					// the first group will change the head of the list
					head = h;
					t->next = at;
				}
				// find the next group
				bh = t;
				h = at;
			} else {
				break;
			}
		}
		
		
		return head;
	}
private:
	void reverseList(ListNode *&h, ListNode *&t) {
		if (h == nullptr || t == nullptr) {
			// impossible
			return;
		}
		if (h == t) {
			// only one node
			return;
		}
		
		ListNode *new_h, *new_t;
		ListNode *ptr, *tmp;
		
		new_h = nullptr;
		ptr = h;
		while (ptr != nullptr) {
			if (new_h == nullptr) {
				new_h = new_t = ptr;
				ptr = ptr->next;
				new_h->next = nullptr;
			} else {
				tmp = ptr->next;
				ptr->next = new_h;
				new_h = ptr;
				ptr = tmp;
			}
		}
		
		h = new_h;
		t = new_t;
	}
};