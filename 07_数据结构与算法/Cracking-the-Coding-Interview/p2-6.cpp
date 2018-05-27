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
		
		// hash the pointers.
		unordered_set<ListNode *> us;
		ListNode *ptr;
		
		ptr = head;
		while (ptr != nullptr) {
			if (us.find(ptr) != us.end()) {
				// the first node of the cycle is found.
				return ptr;
			} else {
				us.insert(ptr);
				ptr = ptr->next;
			}
		}
		
		// the list has no cycle.
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