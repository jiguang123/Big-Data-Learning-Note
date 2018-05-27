// 2CE, 1RE, 1TLE, 2WA, 1AC, never write your code in a hurry.
#include <climits>
#include <cstring>
using namespace std;

class Solution {
public:
    int atoi(const char *str) {
		int i, len;
		int flag;
		long long int result = 0;
		
		if (str == NULL) {
			return result;
		} else if (str[i] == '-') {
			flag = -1;
			++i;
		} else if (str[i] == '+') {
			flag = +1;
			++i;
		} else {
			flag = +1;
		}
		
		long long int int_min, int_max;
		
		int_min = INT_MIN;
		int_max = INT_MAX;
		while (i < len) {
			if (s[i] >= '0' && s[i] < '9') {
				result = result * 10 + (s[i] - '0');
				if (flag == -1) {
					if (-result < int_min) {
						// underflow
						return int_min;
					}
				} else {
					if (result > int_max) {
						// overflow
						return int_max;
					}
				}
			}
			++i;
		}
		
		return flag * result;
	}
};