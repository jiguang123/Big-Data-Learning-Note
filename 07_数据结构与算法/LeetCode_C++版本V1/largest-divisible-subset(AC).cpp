// 1AC, excellent.
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        vector<int> result;

        if (n <= 0) {
            return result;
        }

        sort(nums.begin(), nums.end());
        int i, j;
        vector<int> dp(n, 1);
        vector<int> back_trace(n);

        for (i = 0; i < n; ++i) {
            back_trace[i] = i;
            for (j = i - 1; j >= 0; --j) {
                if (nums[i] % nums[j]) {
                    continue;
                }
                if (dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                    back_trace[i] = j;
                }
            }
        }

        int max_len = 1;
        int max_i = 0;
        for (i = 1; i < n; ++i) {
            if (dp[i] > max_len) {
                max_len = dp[i];
                max_i = i;
            }
        }

        i = max_i;
        while (i != back_trace[i]) {
            result.push_back(nums[i]);
            i = back_trace[i];
        }
        result.push_back(nums[i]);
        reverse(result.begin(), result.end());

        return result;
    }
};
