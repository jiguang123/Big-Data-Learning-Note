// 3CE, 1TLE, 2WA, 1AC, O(n^2) solution with DP, space can be optimized.
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
		int len1;
		int len2;
		int len3;
		
		len1 = (int)s1.length();
		len2 = (int)s2.length();
		len3 = (int)s3.length();
		if (len3 != len1 + len2) {
			return false;
		}
		
		if (len1 == 0) {
			return s2 == s3;
		} else if (len2 == 0) {
			return s1 == s3;
		}
		
		int i, j;
		dp.resize(len1 + 1);
		for (i = 0; i < len1 + 1; ++i) {
			dp[i].resize(len2 + 1);
		}
		
		dp[0][0] = 1;
		for (i = 1; i <= len1; ++i) {
			if (dp[i - 1][0] && s3[i - 1] == s1[i - 1]) {
				dp[i][0] = 1;
			}
		}
		for (j = 1; j <= len2; ++j) {
			if (dp[0][j - 1] && s3[j - 1] == s2[j - 1]) {
				dp[0][j] = 1;
			}
		}
		for (i = 1; i <= len1; ++i) {
			for (j = 1; j <= len2; ++j) {
				dp[i][j] = 0;
				dp[i][j] = dp[i][j] || (dp[i - 1][j] && (s3[i + j - 1] == s1[i - 1]));
				dp[i][j] = dp[i][j] || (dp[i][j - 1] && (s3[i + j - 1] == s2[j - 1]));
			}
		}
		int result = dp[len1][len2];
		
		for (i = 0; i < len1 + 1; ++i) {
			dp[i].clear();
		}
		dp.clear();
		
		return result == 1;
    }
private:
	vector<vector<int> > dp;
};