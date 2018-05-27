// 1AC, old
#include <stack>
using namespace std;

class MinStack {
public:
    void push(int x) {
        if (ms.empty() || ms.top() >= x) {
            ms.push(x);
        }
        s.push(x);
    }

    void pop() {
        if (s.top() == ms.top()) {
            ms.pop();
        }
        s.pop();
    }

    int top() {
        return s.top();
    }

    int getMin() {
        return ms.top();
    }
private:
    stack<int> s, ms;
};