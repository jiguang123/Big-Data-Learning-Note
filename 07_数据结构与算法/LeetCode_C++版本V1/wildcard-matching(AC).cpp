// 2CE, 4WA, 1AC, O(m + n) solution, not so easy to understand.
#include <cstring>
using namespace std;

class Solution {
public:
	bool isMatch(const char *s, const char *p) {
		if (s == nullptr || p == nullptr) {
			return false;
		}
		
		int ls, lp;
		
		ls = strlen(s);
		lp = strlen(p);
		
		if (ls == lp && lp == 0) {
		    return true;
		}
		
		if (lp == 0) {
			return false;
		}
		
		// from here on, ls and lp are guaranteed to be non-zero.
		int i, j;
		int last_star_p;
		int last_star_s;
		
		i = j = 0;
		last_star_p = -1;
		last_star_s = 0;
		while (j < ls) {
			if (p[i] == '?' || p[i] == s[j]) {
				++i;
				++j;
			} else if (p[i] == '*') {
				last_star_p = i;
				++i;
				last_star_s = j;
			} else if (last_star_p != -1) {
				// backtrack to the last '*', and move to the next letter in s
				i = last_star_p + 1;
				j = last_star_s + 1;
				++last_star_s;
			} else {
				return false;
			}
		}
		while (p[i] == '*') {
			// skip the trailing stars
			++i;
		}
		
		return i == lp;
	}
};