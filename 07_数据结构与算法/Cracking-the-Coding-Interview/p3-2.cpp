// 3.2 Design a modified stack that in addition to Push and Pop can also provide minimum element present in the stack via Min function.
#include <climits>
#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;

class MinStack {
public:
	bool empty() {
		return st.empty();
	}
	
	void push(int val) {
		st.push(val);
		if (min_st.empty() || val <= min_st.top()) {
			min_st.push(val);
		}
	}
	
	void pop() {
		if (st.empty()) {
			return;
		}
		if (st.top() == min_st.top()) {
			min_st.pop();
		}
		st.pop();
	}
	
	int top() {
		if (st.empty()) {
			return INT_MIN;
		}
		return st.top();
	}
	
	int min() {
		if (st.empty()) {
			return INT_MIN;
		}
		return min_st.top();
	}
private:
	stack<int> st;
	stack<int> min_st;
};

int main()
{
	char s[100];
	int op;
	MinStack st;
	
	while (scanf("%s", s) == 1 && strcmp(s, "END") != 0) {
		if (strcmp(s, "PUSH") == 0) {
			scanf("%d", &op);
			st.push(op);
			printf("push=%d\n", op);
		} else if (strcmp(s, "POP") == 0) {
			op = st.top();
			st.pop();
			printf("pop=%d\n", op);
		} else if (strcmp(s, "TOP") == 0) {
			printf("top=%d\n", st.top());
		} else if (strcmp(s, "MIN") == 0) {
			printf("min=%d\n", st.min());
		}
	}
	
	return 0;
}