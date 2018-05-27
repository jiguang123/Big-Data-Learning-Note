// 2.1 Remove duplicates from a linked list
// inefficient without hashing space
#include <cstdio>
#include <unordered_set>
using namespace std;

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x): val(x), next(nullptr) {};
};

class Solution {
public:
	void removeDuplicates(ListNode *head) {
		if (head == nullptr) {
			return;
		}
		
		struct ListNode *ptr, *del, *tmp;
		
		ptr = head;
		while (ptr != nullptr && ptr->next != nullptr) {
			del = ptr;
			while (del->next != nullptr) {
				if (ptr->val == del->next->val) {
					tmp = del->next;
					del->next = tmp->next;
					delete tmp;
				} else {
					del = del->next;
				}
			}
			ptr = ptr->next;
		}
	}
};

int main()
{
	int i;
	int n;
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
		
		// remove duplicates from the list
		sol.removeDuplicates(head);
		
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