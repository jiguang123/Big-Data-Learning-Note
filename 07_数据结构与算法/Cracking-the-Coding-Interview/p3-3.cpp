// 3.3 Implement a stack with multiple sub-stacks. If one substack exceeds some threshold, allocate a new stack.
#include <cstdio>
#include <stack>
#include <vector>
using namespace std;

template <class T>
class StackSet {
public:
	StackSet(size_t capacity = 1): mcapacity(capacity), msize(0) {}
	
	void push(T val) {
		if (mdata.empty() || mdata[mdata.size() - 1].size() == mcapacity) {
			mdata.push_back(stack<T>());
		}
		mdata[mdata.size() - 1].push(val);
		++msize;
	}
	
	void pop() {
		if (mdata.empty()) {
			return;
		}
		
		mdata[mdata.size() - 1].pop();
		--msize;
		while (!mdata.empty() && mdata[mdata.size() - 1].empty()) {
			mdata.pop_back();
		}
	}
	
	void popAt(size_t idx) {
		if (mdata.empty()) {
			return;
		}
		
		if (idx < 0 || idx > mdata.size() - 1) {
			pop();
			return;
		}
		
		if (mdata[idx].empty()) {
			return;
		}
		
		mdata[idx].pop();
		--msize;
	}
	
	T top() {
		return mdata[mdata.size() - 1].top();
	}
	
	size_t size() {
		return msize;
	}
private:
	vector<stack<T> > mdata;
	size_t mcapacity;
	size_t msize;
};

int main()
{
	char str[100];
	int val;
	
	scanf("%d", &val);
	StackSet<int> ss(val);
	while (scanf("%s", str) == 1) {
		if (strcmp(str, "end") == 0) {
			break;
		} else if (strcmp(str, "push") == 0) {
			scanf("%d", &val);
			ss.push(val);
		} else if (strcmp(str, "pop") == 0) {
			ss.pop();
		} else if (strcmp(str, "top") == 0) {
			printf("top=%d\n", ss.top());
		} else if (strcmp(str, "size") == 0) {
			printf("size=%u\n", ss.size());
		} else if (strcmp(str, "popat") == 0) {
			scanf("%d", &val);
			ss.popAt(val);
		}
	}
	
	return 0;
}