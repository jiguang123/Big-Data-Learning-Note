// 2.6 You have a circular Linked List: a->b->c->d->e->c. Find where the cycle starts.
#include <cstdio>
#include <unordered_set>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x): val(x), next(nullptr) {};
};

class Solution {
public:
	ListNode* firstFirstNodeInCycle(ListNode *head) {
		if (head == nullptr) {
			return head;
		}
		
		ListNode *p1, *p2;
		
		p1 = head;
		while (p1 != nullptr) {
			p2 = head;
			while (p2 != p1->next && p2 != nullptr) {
				if (p2 == p1) {
					break;
				} else {
					p2 = p2->next;
				}
			}
			if (p2 == p1->next) {
				return p2;
			} else {
				p1 = p1->next;
			}
		}
		
		return nullptr;
	}
};

int main()
{
	int i;
	int n, k;
	int val;
	struct ListNode *head, *tail, *ptr;
	Solution sol;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		// create a linked list
		ptr = head = tail = nullptr;
		for (i = 0; i < n; ++i) {
			scanf("%d", &val);
			if (head == nullptr) {
				head = ptr = new ListNode(val);
			} else {
				ptr->next = new ListNode(val);
				ptr = ptr->next;
			}
		}
		tail = ptr;
		
		// create a cycle in the list
		scanf("%d", &k);
		if (k >= 1 && k <= n) {
			ptr = head;
			for (i = 1; i < k; ++i) {
				ptr = ptr->next;
			}
			tail->next = ptr;
		}
		
		// find the first node in the cycle.
		ListNode *first_node = sol.firstFirstNodeInCycle(head);
		if (first_node != nullptr) {
			printf("%d\n", first_node->val);
		} else {
			printf("no cycle\n");
		}
		
		/*
		// print the list
		ptr = head;
		for (i = 0; i < n; ++i) {
			printf("%d->", ptr->val);
			ptr = ptr->next;
		}
		printf("\n");
		*/

		// delete the list
		for (i = 0; i < n; ++i) {
			ptr = head->next;
			delete head;
			head = ptr;
		}
	}
	
	return 0;
}