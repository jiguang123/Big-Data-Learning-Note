// 1.3 Given two strings, write a method to decide if one is a permutation of the other.
// count them.
#include <cstdio>
#include <cstring>
using namespace std;

class Solution {
public:
	bool isPermutation(const char *s, const char *p) {
		if (nullptr == s || nullptr == p) {
			return false;
		}

		size_t len = strlen(s);
		if (len != strlen(p)) {
			return false;
		}

		int a[256];
		memset(a, 0, 256 * sizeof(int));

		size_t i;
		for (i = 0; i < len; ++i) {
			++a[s[i]];
			--a[p[i]];
		}
		for (i = 0; i < 256; ++i) {
			if (a[i]) {
				return false;
			}
		}
		return true;
	}
};

int main()
{
	char s[1000], p[1000];
	Solution sol;

	while (scanf("%s%s", s, p) == 2) {
		printf("\"%s\" is ", s);
		if (!sol.isPermutation(s, p)) {
			printf("not ");
		}
		printf("a permutation of \"%s\".\n", p);
	}

	return 0;
}