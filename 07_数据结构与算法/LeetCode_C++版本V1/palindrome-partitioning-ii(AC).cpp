// 1WA, 1AC, O(n^2) solution with DP
#include <string>
using namespace std;

class Solution {
public:
    int minCut(string s) {
		int **pal = nullptr;
		int *dp = nullptr;
		int len = (int)s.size();
		
		if (len <= 1) {
			return 0;
		}
		
		pal = new int*[len];
		dp = new int[len + 1];
		
		int i, j;
		for (i = 0; i < len; ++i) {
			pal[i] = new int[len];
		}
		for (i = 0; i < len; ++i) {
			for (j = 0; j < len; ++j) {
				pal[i][j] = 0;
			}
		}
		
		// pal[i][j] means whether the substring s[i:j] is a palindrome.
		for (i = 0; i < len; ++i) {
			pal[i][i] = 1;
		}
		for (i = 0; i < len - 1; ++i) {
			pal[i][i + 1] = (s[i] == s[i + 1]) ? 1 : 0;
		}
		for (i = 2; i <= len - 1; ++i) {
			for (j = 0; j + i < len; ++j) {
				pal[j][j + i] = (pal[j + 1][j + i - 1] && (s[j] == s[j + i])) ? 1 : 0;
			}
		}
		
		// dp[i] means the minimal number of segments the substring s[0:i] 
		// must be cut, so that they're all palindromes.
		dp[0] = 0;
		for (i = 1; i <= len; ++i) {
			dp[i] = i;
			for (j = 0; j < i; ++j) {
				if (pal[j][i - 1]) {
					dp[i] = mymin(dp[j] + 1, dp[i]);
				}
			}
		}
		
		int ans = dp[len];
		for (i = 0; i < len; ++i) {
			delete[] pal[i];
		}
		delete[] pal;
		delete[] dp;
		
		return ans - 1;
    }
private:
	int mymin(const int x, const int y) {
		return (x < y ? x : y);
	}
};