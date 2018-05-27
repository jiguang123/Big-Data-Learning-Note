// 18.5 Given a text file containing words, find the shortest distance between two words.
#include <algorithm>
#include <climits>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int _val = 0): val(_val), next(nullptr) {};
};

class Solution {
public:
	int minDist(ListNode *head1, ListNode *head2)
	{
		// the two list records the forward indices of two word, i.e. their occurrence position.
		// For example, 1->4->5->nullptr means the word appears at 1st, 4th and 5th line.
		
		int min_dist = INT_MAX;
		ListNode *p1, *p2;
		
		p1 = head1;
		p2 = head2;
		while (p1 != nullptr && p2 != nullptr) {
			if (p1->val < p2->val) {
				min_dist = min(min_dist, p2->val - p1->val);
				p1 = p1->next;
			} else {
				min_dist = min(min_dist, p1->val - p2->val);
				p2 = p2->next;
			}
		}
		
		return min_dist;
	}
};