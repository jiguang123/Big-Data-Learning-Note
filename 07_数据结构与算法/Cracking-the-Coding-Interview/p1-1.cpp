// 1.1 Implement an algorithm to determine if a string has all unique characters. What if you cannot use additional data structure?
#include <cstdio>
#include <cstring>
using namespace std;

class Solution {
public:
	bool isAllUnique(const char *s) {
		if (nullptr == s) {
			return false;
		}
		int i;

		int a[256];
		memset(a, 0, 256 * sizeof(int));
		for (i = 0; s[i]; ++i) {
			if (a[s[i]]) {
				return false;
			} else {
				a[s[i]] = 1;
			}
		}

		return true;
	};
};

int main()
{
	Solution sol;
	char s[100];
	
	while (scanf("%s", s) == 1) {
		if (sol.isAllUnique(s)) {
			printf("Unique.\n");
		} else {
			printf("Not unique.\n");
		}
	}

	return 0;
}