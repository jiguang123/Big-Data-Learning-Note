// 1AC, DP solution with O(n) time and space.
class Solution {
public:
	int candy(vector<int> &ratings) {
		int i, n;
		
		n = (int)ratings.size();
		if (n == 0) {
			return 0;
		}
		
		vector<int> candy;
		int result;
		
		candy.resize(n);
		for (i = 0; i < n; ++i) {
			candy[i] = 1;
		}
		for (i = 0; i <= n - 2; ++i) {
			if (ratings[i] < ratings[i + 1]) {
				// at least one more candy
				candy[i + 1] = candy[i] + 1;
			}
		}
		for (i = n - 2; i >= 0; --i) {
			if (ratings[i] > ratings[i + 1] && candy[i] <= candy[i + 1]) {
				candy[i] = candy[i + 1] + 1;
			}
		}
		result = 0;
		for (i = 0; i < n; ++i) {
			result += candy[i];
		}
		candy.clear();
		
		return result;
	}
};