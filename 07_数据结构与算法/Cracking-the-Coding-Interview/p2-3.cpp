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
	void deleteThatNode(ListNode *ptr) {
		if (ptr != nullptr && ptr->next != nullptr) {
			struct ListNode *tmp = ptr->next;
			ptr->val = tmp->val;
			ptr->next = tmp->next;
			delete tmp;
		}
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
		
		// remove a node from middle of the list
		scanf("%d", &k);
		k = k < 1 ? 1 : k;
		k = k > n ? n : k;
		ptr = head;
		for (i = 1; i < k; ++i) {
			ptr = ptr->next;
		}
		sol.deleteThatNode(ptr);
		
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