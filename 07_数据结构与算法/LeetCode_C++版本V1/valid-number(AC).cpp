// 1CE, 3WA, 1AC, good, but not good enough.
#include <cstring>
using namespace std;

class Solution {
public:
    bool isNumber(const char *s) {
		int i, len;
		
		if (s == nullptr) {
			return false;
		}
		
		len = strlen(s);
		// skip the trailing spaces
		while (len - 1 >= 0 && s[len - 1] == ' ') {
			--len;
		}
		i = 0;
		
		// skip the leading spaces
		while (i < len && s[i] == ' ') {
			++i;
		}
		if (i == len) {
			return false;
		}
		
		// an optional sign
		if (s[i] == '-' || s[i] == '+') {
			++i;
		}
		if (i == len) {
			return false;
		}
		
		// the part before 'e' or 'E'
		int dot_count = 0;
		int digit_count = 0;
		while (i < len && s[i] != 'e' && s[i] != 'E') {
			if (s[i] >= '0' && s[i] <= '9') {
				++digit_count;
			} else if (s[i] == '.') {
				if (dot_count > 0) {
					return false;
				} else {
					++dot_count;
				}
			} else {
				return false;
			}
			++i;
		}
		if (i == len) {
			// no 'e' or 'E'
			if (digit_count > 0) {
				return true;
			} else {
				return false;
			}
		} else if (digit_count == 0) {
			return false;
		}
		
		++i;
		if (i == len) {
			// no exponent after 'e' or 'E'
			// 1.2E
			return false;
		}
		
		if (s[i] == '-' || s[i] == '+') {
			++i;
		}
		if (i == len) {
			// no digit after 'e' or 'E'
			// 1.2E+
			// 1.3e-
			return false;
		}
		while (i < len) {
			if (s[i] >= '0' && s[i] <= '9') {
				++i;
			} else {
				return false;
			}
		}
		
		return true;
    }
};