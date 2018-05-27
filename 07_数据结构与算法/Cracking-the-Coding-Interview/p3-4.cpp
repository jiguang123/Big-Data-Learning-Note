// 3.4 Implement Hanoi Tower with three stacks.
#include <cstdio>
#include <stack>
using namespace std;

class Solution {
public:
	void initHanoiTower(int n) {
		int i;
		
		clearHanoiTower();
		
		for (i = n; i >= 1; --i) {
			s[0].push(i);
		}
	}
	
	void moveHanoiTower(int n, int from, int to) {
		if (from == to) {
			return;
		}
		
		if ((int)s[from].size() < n) {
			return;
		}
		
		if (n == 1) {
			s[to].push(s[from].top());
			s[from].pop();
			return;
		}
		
		int i;
		for (i = 0; i < 3; ++i) {
			b[i] = false;
		}
		b[from] = true;
		b[to] = true;
		int other;
		for (i = 0; i < 3; ++i) {
			if (!b[i]) {
				other = i;
				break;
			}
		}

		moveHanoiTower(n - 1, from, other);
		moveHanoiTower(1, from, to);
		moveHanoiTower(n - 1, other, to);
	}
	
	void clearHanoiTower() {
		int i;
		
		for (i = 0; i < 3; ++i) {
			while (!s[i].empty()) {
				s[i].pop();
			}
		}
	}
	
	void printHanoiTower() {
		stack<int> ss[3];
		int i;
		
		for (i = 0; i < 3; ++i) {
			ss[i] = s[i];
			printf("Tower %d:", i + 1);
			while (!ss[i].empty()) {
				printf(" %d", ss[i].top());
				ss[i].pop();
			}
			printf("\n");
		}
	}
private:
	stack<int> s[3];
	int b[3];
};

int main()
{
	int n;
	Solution sol;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		sol.initHanoiTower(n);
		
		printf("At the beginning:\n");
		sol.printHanoiTower();
		printf("\n");

		sol.moveHanoiTower(n, 0, 2);
		
		printf("At the end:\n");
		sol.printHanoiTower();
		printf("\n");
	}
	
	return 0;
}