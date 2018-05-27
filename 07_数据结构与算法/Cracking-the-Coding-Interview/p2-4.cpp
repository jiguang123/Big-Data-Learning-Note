// 2.4 Write code to partition a linked list around a value x, such that all nodes less than x comes before all nodes greater than or equal to x.
#include <cstdio>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x): val(x), next(nullptr) {};
};

class Solution {
public:
	ListNode* partitionList(ListNode *head, int x) {
		if (head == nullptr) {
			return head;
		}
		
		ListNode *h1, *t1, *h2, *t2;
		ListNode *ptr;
		
		h1 = t1 = nullptr;
		h2 = t2 = nullptr;
		ptr = head;
		while (ptr != nullptr) {
			if (ptr->val < x) {
				if (h1 == nullptr) {
					h1 = t1 = ptr;
				} else {
					t1->next = ptr;
					t1 = t1->next;
				}
				ptr = ptr->next;
				t1->next = nullptr;
			} else {
				if (h2 == nullptr) {
					h2 = t2 = ptr;
				} else {
					t2->next = ptr;
					t2 = t2->next;
				}
				ptr = ptr->next;
				t2->next = nullptr;
			}
		}
		if (h1 == nullptr) {
			return h2;
		} else if (h2 == nullptr) {
			return h1;
		} else {
			t1->next = h2;
			return h1;
		}
	}
};

int main()
{
	int i;
	int n, x;
	int val;
	struct ListNode *head, *ptr;
	Solution sol;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		// create a linked list
		ptr = head = nullptr;
		for (i = 0; i < n; ++i) {
			scanf("%d", &val);
			if (head == nullptr) {
				head = ptr = new ListNode(val);
			} else {
				ptr->next = new ListNode(val);
				ptr = ptr->next;
			}
		}
		
		// partition the list around value x.
		scanf("%d", &x);
		head = sol.partitionList(head, x);
		
		// print the list
		printf("%d", head->val);
		ptr = head->next;
		while (ptr != nullptr) {
			printf("->%d", ptr->val);
			ptr = ptr->next;
		}
		printf("\n");
		
		// delete the list
		while (head != nullptr) {
			ptr = head->next;
			delete head;
			head = ptr;
		}
	}
	
	return 0;
}