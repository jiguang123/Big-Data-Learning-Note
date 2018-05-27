// 1AC, space-optimized version using DP.
#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
	int minDistance(string word1, string word2) {
		int n1, n2;
		
		if (n1 < n2) {
			return minDistance(word2, word1);
		}
		
		n1 = (int)word1.length();
		n2 = (int)word2.length();
		if (n1 == 0) {
			return n2;
		} else if (n2 == 0) {
			return n1;
		}
		
		int **dp;

		dp = new int*[2];
		dp[0] = new int[2 * (n2 + 1)];
		dp[1] = dp[0] + (n2 + 1);
		
		int i, j;
		
		for (j = 0; j <= n2; ++j) {
			dp[0][j] = j;
		}
		
		int flag = 1;
		for (i = 1; i <= n1; ++i) {
			dp[flag][0] = i;
			for (j = 1; j <= n2; ++j) {
				dp[flag][j] = min(dp[!flag][j] , dp[flag][j - 1]) + 1;
				if (word1[i - 1] == word2[j - 1]) {
					dp[flag][j] = min(dp[flag][j], dp[!flag][j - 1]);
				} else {
					dp[flag][j] = min(dp[flag][j], dp[!flag][j - 1] + 1);
				}
			}
			flag = !flag;
		}
		int result = dp[!flag][n2];
		
		delete[] dp[0];
		delete[] dp;
		
		return result;
	}
};