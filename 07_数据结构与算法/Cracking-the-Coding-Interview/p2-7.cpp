// 2.7 To Check the given linked list is palindrome or not?
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
	bool isPalindromeList(ListNode *head) {
		if (head == nullptr) {
			return false;
		}
		if (head->next == nullptr) {
			return true;
		}
		
		ListNode *t1, *run, *h2;
		
		t1 = run = head;
		while (run->next != nullptr && run->next->next != nullptr) {
			t1 = t1->next;
			run = run->next->next;
		}
		h2 = t1->next;
		t1->next = nullptr;
		h2 = reverseList(h2);
		
		ListNode *p1, *p2;
		p1 = head;
		p2 = h2;
		while (p2 != nullptr) {
			if (p1->val != p2->val) {
				break;
			} else {
				p1 = p1->next;
				p2 = p2->next;
			}
		}
		bool res = (p2 == nullptr);
		
		h2 = reverseList(h2);
		t1->next = h2;
		
		return res;
	}
private:
	ListNode* reverseList(ListNode* head) {
		if (head == nullptr) {
			return head;
		}
		
		ListNode* new_head = nullptr;
		ListNode* ptr;
		
		while (head != nullptr) {
			if (new_head == nullptr) {
				new_head = head;
				head = head->next;
				new_head->next = nullptr;
			} else {
				ptr = head->next;
				head->next = new_head;
				new_head = head;
				head = ptr;
			}
		}
		
		return new_head;
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
		
		// check if the list is a palindrome
		if (sol.isPalindromeList(head)) {
			printf("It's a palindrome.\n");
		} else {
			printf("It's not a palindrome.\n");
		}
		
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