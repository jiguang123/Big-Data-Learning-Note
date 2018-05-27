// 1AC, space optimized.
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
		
		if (len1 < len2) {
			return isInterleave(s2, s1, s3);
		}
		
		int i, j;
		dp.resize(2);
		for (i = 0; i < 2; ++i) {
			dp[i].resize(len2 + 1);
		}
		
		dp[0][0] = 1;
		for (j = 1; j <= len2; ++j) {
			if (dp[0][j - 1] && s3[j - 1] == s2[j - 1]) {
				dp[0][j] = 1;
			} else {
				dp[0][j] = 0;
			}
		}
		
		int flag = 1, nflag = !flag;
		for (i = 1; i <= len1; ++i) {
			if (dp[nflag][0] && s3[i - 1] == s1[i - 1]) {
				dp[flag][0] = 1;
			} else {
				dp[flag][0] = 0;
			}
			for (j = 1; j <= len2; ++j) {
				dp[flag][j] = 0;
				dp[flag][j] = dp[flag][j] || (dp[nflag][j] && (s3[i + j - 1] == s1[i - 1]));
				dp[flag][j] = dp[flag][j] || (dp[flag][j - 1] && (s3[i + j - 1] == s2[j - 1]));
			}
			flag = !flag;
			nflag = !flag;
		}
		int result = dp[nflag][len2];
		
		for (i = 0; i < 2; ++i) {
			dp[i].clear();
		}
		dp.clear();
		
		return result == 1;
    }
private:
	vector<vector<int> > dp;
};