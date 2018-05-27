// 1RE, 4WA, 1AC, that was quite a problem... no DP and no recursion is tough.
#include <cstring>
#include <vector>
using namespace std;

class Solution {
public:
	bool isMatch(const char *s, const char *p) {
		int i, j;
		int ls, lp;
		vector<int> last_i_arr;
		vector<int> last_j_arr;
		
		if (s == nullptr || p == nullptr) {
			return false;
		}
		
		ls = strlen(s);
		lp = strlen(p);
		if (lp == 0) {
			// empty patterns are regarded as match.
			return ls == 0;
		}
		
		// validate the pattern string.
		for (j = 0; j < lp; ++j) {
			if (p[j] == '*' && (j == 0 || p[j - 1] == '*')) {
				// invalid pattern string, can't match.
				return false;
			}
		}
		
		int last_i, last_j;
		
		i = j = 0;
		last_i = -1;
		last_j = -1;
		while (i < ls) {
			if (j + 1 < lp && p[j + 1] == '*') {
				last_i_arr.push_back(i);
				last_j_arr.push_back(j);
				++last_i;
				++last_j;
				j += 2;
			} else if (p[j] == '.' || s[i] == p[j]) {
				++i;
				++j;
			} else if (last_j != -1) {
				if (p[last_j_arr[last_j]] == '.' || s[last_i_arr[last_i]] == p[last_j_arr[last_j]]) {
					// current backtracking position is still available.
					i = (++last_i_arr[last_i]);
					j = last_j_arr[last_j] + 2;
				} else if (last_j > 0) {
					while (last_j  >= 0) {
						// backtrack to the last backtracking point.
						--last_i;
						--last_j;
						last_i_arr.pop_back();
						last_j_arr.pop_back();
						if (last_j >= 0 && (p[last_j_arr[last_j]] == '.' || s[last_i_arr[last_i]] == p[last_j_arr[last_j]])) {
							i = (++last_i_arr[last_i]);
							j = last_j_arr[last_j] + 2;
							break;
						}
					}
					if (last_j == -1) {
						return false;
					}
				} else {
					// no more backtracking is possible.
					return false;
				}
			} else {
				return false;
			}
		}
		
		while (j < lp) {
			if (j + 1 < lp && p[j + 1] == '*') {
				j += 2;
			} else {
				break;
			}
		}
		
		last_i_arr.clear();
		last_j_arr.clear();
		return j == lp;
	}
};