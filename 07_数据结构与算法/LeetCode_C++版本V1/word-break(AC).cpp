// 1CE, 1TLE, 1AC, O(n^2) solution with DP. DFS will cause timeout.
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
    bool wordBreak(string s, unordered_set<string> &dict) {
		int n;
		int i, j;
		string str;
		vector<int> dp;
		
		n = (int)s.length();
		if (n == 0 || dict.empty()) {
			return false;
		}
		dp.resize(n);
		for (i = 0; i < n; ++i) {
			str = s.substr(0, i + 1);
			if (dict.find(str) != dict.end()) {
				dp[i] = 1;
			} else {
				for (j = 0; j < i; ++j) {
					if (dp[j] && dict.find(s.substr(j + 1, i - j)) != dict.end()) {
						dp[i] = 1;
						break;
					}
				}
				if (j == i) {
					dp[i] = 0;
				}
			}
		}
		
		i = dp[n - 1];
		dp.clear();
		return i == 1;
    }
};