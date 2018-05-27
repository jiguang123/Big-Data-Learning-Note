// 2.1 Remove duplicates from a linked list
// efficient with hashing space
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
		
		unordered_set<int> us;
		struct ListNode *ptr, *del;
		
		us.insert(head->val);
		ptr = head;
		while (ptr->next != nullptr) {
			if (us.find(ptr->next->val) != us.end()) {
				// duplicate value
				del = ptr->next;
				ptr->next = del->next;
				delete del;
			} else {
				ptr = ptr->next;
				us.insert(ptr->val);
			}
		}
		
		us.clear();
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