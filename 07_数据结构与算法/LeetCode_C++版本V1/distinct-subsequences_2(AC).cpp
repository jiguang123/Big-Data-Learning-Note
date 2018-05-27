// 1AC, spatially optimized version
#include <cstring>
#include <vector>
using namespace std;

class Solution {
public:
	int numDistinct(string S, string T) {
		int **dp;
		int ls, lt;
		int result;
		int i, j;
		
		ls = (int)S.size();
		lt = (int)T.size();
		if (ls == 0 || lt == 0 || ls < lt) {
			return 0;
		}
		
		dp = new int*[2];
		for (i = 0; i < 2; ++i) {
			dp[i] = new int[lt + 1];
		}
		for (i = 0; i < 2; ++i) {
			for (j = 0; j <= lt; ++j) {
				dp[i][j] = 0;
			}
		}
		
		if (S[0] == T[0]) {
			dp[1][1] = 1;
		}
		
		int flag;
		flag = 0;
		for (i = 2; i <= ls; ++i) {
			dp[flag][0] = 0;
			if (S[i - 1] == T[0]) {
				dp[flag][1] = dp[!flag][1] + 1;
			} else {
				dp[flag][1] = dp[!flag][1];
			}
			for (j = 2; j <= lt; ++j) {
				if (S[i - 1] == T[j - 1]) {
					dp[flag][j] = dp[!flag][j] + dp[!flag][j - 1];
				} else {
					dp[flag][j] = dp[!flag][j];
				}
			}
			flag = !flag;
		}
		flag = !flag;
		result = dp[flag][lt];
		for (i = 0; i < 2; ++i) {
			delete[] dp[i];
		}
		delete[] dp;
		dp = NULL;
		
		return result;
	}
};