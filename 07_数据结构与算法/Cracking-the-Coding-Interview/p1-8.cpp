// 1.8 Assume you have a method isSubstring which checks if one word is a substring of another. Given two strings, s1 and s2, write code to check if s2 is a rotation of s1 using only one call to isSubstring (i.e., ¡°waterbottle¡± is a rotation of ¡°erbottlewat¡±).
#include <cstdio>
#include <cstring>
using namespace std;

class Solution {
public:
	bool isStringRotation(char *s1, char *s2) {
		if (s1 == nullptr || s2 == nullptr) {
			return false;
		}
		
		int len1, len2;
		
		len1 = strlen(s1);
		len2 = strlen(s2);
		if (len1 != len2) {
			return false;
		}
		
		const int MAXLEN = 1005;
		static char tmp[MAXLEN];
		
		tmp[0] = 0;
		strcat(tmp, s1);
		strcat(tmp, s1);
		return strstr(tmp, s2) != nullptr;
	}
private:
	bool isSubstring(char *haystack, char *needle) {
		if (haystack == nullptr || needle == nullptr) {
			return false;
		}
		
		return strstr(haystack, needle) != nullptr;
	}
};

int main()
{
	char s1[1005];
	char s2[1005];
	Solution sol;
	
	while (scanf("%s%s", s1, s2) == 2) {
		printf("\"%s\" is ", s2);
		if (!sol.isStringRotation(s1, s2)) {
			printf("not ");
		}
		printf("a rotation of \"%s\".\n", s1);
	}
	
	return 0;
}