// 3.6 Try to sort the elements in a stack with the aid of at most one more stack.
#include <cstdio>
#include <stack>
using namespace std;

class Solution {
public:
	void sortStack(stack<int> &s1) {
		if (s1.empty()) {
			return;
		}
		// extra O(n) here
		stack<int> s2;
		// extra O(1) here
		int val;
		
		while (!s1.empty()) {
			if (s2.empty() || s1.top() <= s2.top()) {
				s2.push(s1.top());
				s1.pop();
			} else {
				val = s1.top();
				s1.pop();
				while (!s2.empty() && s2.top() < val) {
					s1.push(s2.top());
					s2.pop();
				}
				s2.push(val);
			}
		}
		while (!s2.empty()) {
			s1.push(s2.top());
			s2.pop();
		}
	}
};

int main()
{
	Solution sol;
	int i, n, val;
	stack<int> st;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < n; ++i) {
			scanf("%d", &val);
			st.push(val);
		}
		sol.sortStack(st);
		
		printf("%d", st.top());
		st.pop();
		while (!st.empty()) {
			printf(" %d", st.top());
			st.pop();
		}
		printf("\n");
	}
	
	return 0;
}