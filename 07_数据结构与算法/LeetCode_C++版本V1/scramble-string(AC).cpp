// 2CE, 2RE, 1AC
class Solution {
public:
	bool isScramble(string s1, string s2) {
		int len1, len2;
		
		len1 = (int)s1.length();
		len2 = (int)s2.length();
		// their lengths must be at least equal
		if (len1 == 0 || len2 == 0 || len1 != len2) {
			return false;
		}
		
		// they must at least anagrams
		int c[256];
		int i, j, k, m;
		for (i = 0; i < 256; ++i) {
			c[i] = 0;
		}
		for (i = 0; i < len1; ++i) {
			++c[s1[i]];
		}
		for (i = 0; i < len2; ++i) {
			--c[s2[i]];
		}
		for (i = 0; i < 256; ++i) {
			if (c[i] != 0) {
				return false;
			}
		}
		
		int n = len1;
		int ***dp;
		dp = new int**[n];
		dp[0] =  new int*[n * n];
		for (i = 1; i < n; ++i) {
			dp[i] = &dp[0][0] + i * n;
		}
		dp[0][0] = new int[n * n * n];
		for (i = 1; i < n * n; ++i) {
			dp[i / n][i % n] = &dp[0][0][0] + i * n;
		}
		
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				for (k = 0; k < n; ++k) {
					dp[i][j][k] = 0;
				}
			}
		}
		
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				if (s1[i] == s2[j]) {
					dp[0][i][j] = 1;
				}
			}
		}
		for (i = 1; i < n; ++i) {
			for (j = 0; j + i < n; ++j) {
				for (k = 0; k + i < n; ++k) {
					for (m = 0; m < i; ++m) {
						dp[i][j][k] = (dp[m][j][k] && dp[i - m - 1][j + m + 1][k + m + 1]) || 
									  (dp[m][j][k + i - m] && dp[i - m - 1][j + m + 1][k]);
						if (dp[i][j][k]) {
							break;
						}
					}
				}
			}
		}
		int result = dp[n - 1][0][0];
		
		delete[] dp[0][0];
		dp[0][0] = nullptr;
		delete[] dp[0];
		dp[0] = nullptr;
		delete[] dp;
		dp = nullptr;
		
		return result == 1;
	}
};