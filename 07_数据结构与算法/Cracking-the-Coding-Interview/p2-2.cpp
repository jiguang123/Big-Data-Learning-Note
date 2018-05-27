// 2.2 Remove a node from middle of a linked list
#include <cstdio>
using namespace std;

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x): val(x), next(nullptr) {};
};

class Solution {
public:
	ListNode* findKthNode(ListNode *head, int k) {
		if (head == nullptr || k < 1) {
			return head;
		}
		struct ListNode *p1, *p2;
		
		p1 = p2 = head;
		int i;
		for (i = 0; i < k; ++i) {
			p2 = p2->next;
			if (p2 == nullptr) {
				return head;
			}
		}
		while (p2 != nullptr) {
			p1 = p1->next;
			p2 = p2->next;
		}
		
		return p1;
	}
};

int main()
{
	int i;
	int n, k;
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
		
		// find the kth node from the end of the list
		scanf("%d", &k);
		ptr = sol.findKthNode(head, k);
		printf("%d\n", ptr->val);
		
		/*
		// print the list
		printf("%d", head->val);
		ptr = head->next;
		while (ptr != nullptr) {
			printf("->%d", ptr->val);
			ptr = ptr->next;
		}
		printf("\n");
		*/
		
		// delete the list
		while (head != nullptr) {
			ptr = head->next;
			delete head;
			head = ptr;
		}
	}
	
	return 0;
}