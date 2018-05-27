#include <algorithm>
#include <climits>
#include <cmath>
#include <vector>
using namespace std;

class Solution {
public:
    Solution() {
        dp.push_back(0);
    }

    int numSquares(int n) {
        int i = dp.size();
        while (i <= n) {
            dp.push_back(calc(i++));
        }
        return dp[n];
    }
private:
    vector<int> dp;
    
    int calc(int n) {
        int i = (int)sqrt(1.0 * n);
        int ans = INT_MAX;
        while (i > 0) {
            ans = min(ans, dp[n - i * i] + 1);
            --i;
        }
        return ans;
    }
};