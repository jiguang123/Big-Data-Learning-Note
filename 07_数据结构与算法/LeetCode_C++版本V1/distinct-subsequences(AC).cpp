// 2RE, 1WA, 1AC, don't use memset on dp[][], although it looks as if it were one block of memory.
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
		if (ls == 0 || lt == 0) {
			return 0;
		}
		
		dp = new int*[ls + 1];
		for (i = 0; i < ls + 1; ++i) {
			dp[i] = new int[lt + 1];
		}
		for (i = 0; i <= ls; ++i) {
			for (j = 0; j <= lt; ++j) {
				dp[i][j] = 0;
			}
		}
		/*
		for (i = 0; i <= ls; ++i) {
			dp[i][0] = 0;
		}
		for (i = 0; i <= lt; ++i) {
			dp[0][i] = 0;
		}
		*/
		for (i = 1; i <= ls; ++i) {
			if (S[i - 1] == T[0]) {
				dp[i][1] = dp[i - 1][1] + 1;
			} else {
				dp[i][1] = dp[i - 1][1];
			}
		}
		
		for (i = 2; i <= ls; ++i) {
			for (j = 2; j <= lt; ++j) {
				if (S[i - 1] == T[j - 1]) {
					dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
				} else {
					dp[i][j] = dp[i - 1][j];
				}
			}
		}
		result = dp[ls][lt];
		for (i = 0; i < ls + 1; ++i) {
			delete[] dp[i];
		}
		delete[] dp;
		dp = NULL;
		
		return result;
	}
};