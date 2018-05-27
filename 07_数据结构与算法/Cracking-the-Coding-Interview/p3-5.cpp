// 3.5 Implement a queue MyQueue using two stacks.
#include <climits>
#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;

template<class T>
class MyQueue {
public:
	bool empty() {
		return s1.empty() && s2.empty();
	}
	
	void push(const T &val) {
		s1.push(val);
	}
	
	void pop() {
		if (s2.empty()) {
			while (!s1.empty()) {
				s2.push(s1.top());
				s1.pop();
			}
		}
		s2.pop();
	}
	
	T front() {
		if (s2.empty()) {
			while (!s1.empty()) {
				s2.push(s1.top());
				s1.pop();
			}
		}
		
		return s2.top();
	}
	
	T back() {
		if (s1.empty()) {
			while (!s2.empty()) {
				s1.push(s2.top());
				s2.pop();
			}
		}
		
		return s1.top();
	}
private:
	stack<T> s1, s2;
};

int main()
{
	MyQueue<int> qq;
	char s[100];
	int op;

	while (scanf("%s", s) == 1) {
		if (strcmp(s, "end") == 0) {
			break;
		} else if (strcmp(s, "push") == 0) {
			scanf("%d", &op);
			qq.push(op);
		} else if (strcmp(s, "pop") == 0) {
			qq.pop();
		} else if (strcmp(s, "front") == 0) {
			printf("%d\n", qq.front());
		} else if (strcmp(s, "back") == 0) {
			printf("%d\n", qq.back());
		}
	}
	
	return 0;
}