// 2.5 Given two numbers represented by two lists, write a function that returns sum list. The sum list is list representation of addition of two input numbers.
// Example First List: 5->6->3 // represents number 365 
// Second List: 8->4->2 // represents number 248 
// Resultant list: 3->1->6 // 
// Note :Any Carry forward should also be added as the new node . Any Comments on the code below
#include <cstdio>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x): val(x), next(nullptr) {};
};

class Solution {
public:
	ListNode* listAddition(ListNode *head1, ListNode *head2) {
		if (head1 == nullptr) {
			return head2;
		} else if (head2 == nullptr) {
			return head1;
		}
		
		int carry = 0;
		int val;
		ListNode *p1, *p2;
		ListNode *head, *tail;
		
		p1 = head1;
		p2 = head2;
		head = tail = nullptr;
		while (p1 != nullptr && p2 != nullptr) {
			val = p1->val + p2->val + carry;
			carry = val / 10;
			val %= 10;
			if (head == nullptr) {
				head = tail = new ListNode(val);
			} else {
				tail->next = new ListNode(val);
				tail = tail->next;
			}
			p1 = p1->next;
			p2 = p2->next;
		}
		while (p1 != nullptr) {
			val = p1->val + carry;
			carry = val / 10;
			val %= 10;
			tail->next = new ListNode(val);
			tail = tail->next;
			p1 = p1->next;
		}
		while (p2 != nullptr) {
			val = p2->val + carry;
			carry = val / 10;
			val %= 10;
			tail->next = new ListNode(val);
			tail = tail->next;
			p2 = p2->next;
		}
		if (carry) {
			tail->next = new ListNode(carry);
			tail = tail->next;
		}
		
		return head;
	}
};

int main()
{
	int i;
	int n1, n2;
	int val;
	struct ListNode *head, *head1, *head2, *ptr;
	Solution sol;
	
	while (scanf("%d%d", &n1, &n2) == 2 && n1 > 0 && n2 > 0) {
		// create two linked lists
		ptr = head1 = nullptr;
		for (i = 0; i < n1; ++i) {
			scanf("%d", &val);
			if (head1 == nullptr) {
				head1 = ptr = new ListNode(val);
			} else {
				ptr->next = new ListNode(val);
				ptr = ptr->next;
			}
		}
		ptr = head2 = nullptr;
		for (i = 0; i < n2; ++i) {
			scanf("%d", &val);
			if (head2 == nullptr) {
				head2 = ptr = new ListNode(val);
			} else {
				ptr->next = new ListNode(val);
				ptr = ptr->next;
			}
		}
		
		// add up the two lists
		head = sol.listAddition(head1, head2);
		
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
		while (head1 != nullptr) {
			ptr = head1->next;
			delete head1;
			head1 = ptr;
		}
		while (head2 != nullptr) {
			ptr = head2->next;
			delete head2;
			head2 = ptr;
		}
	}
	
	return 0;
}