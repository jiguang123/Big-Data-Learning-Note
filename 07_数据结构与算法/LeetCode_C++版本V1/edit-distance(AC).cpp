// 2CE, 2WA, 1AC, standard DP problem.
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

		dp = new int*[n1 + 1];
		dp[0] = new int[(n1 + 1) * (n2 + 1)];
		
		int i, j;
		for (i = 1; i <= n1; ++i) {
			dp[i] = dp[0] + (i * (n2 + 1));
		}
		
		dp[0][0] = 0;
		for (i = 1; i <= n1; ++i) {
			dp[i][0] = i;
		}
		for (j = 1; j <= n2; ++j) {
			dp[0][j] = j;
		}
		
		for (i = 1; i <= n1; ++i) {
			for (j = 1; j <= n2; ++j) {
				dp[i][j] = min(dp[i - 1][j] , dp[i][j - 1]) + 1;
				if (word1[i - 1] == word2[j - 1]) {
					dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
				} else {
					dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
				}
			}
		}
		int result = dp[n1][n2];
		
		delete[] dp[0];
		delete[] dp;
		
		return result;
	}
};