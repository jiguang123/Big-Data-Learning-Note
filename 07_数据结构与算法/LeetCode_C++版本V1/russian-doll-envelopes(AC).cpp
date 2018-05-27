// 1AC, straight-forward DP solution， O(N ^ 2).
#include <algorithm>
using namespace std;

typedef pair<int, int> PP;

bool comp(const PP &p1, const PP &p2)
{
    if (p1.first != p2.first) {
        return p1.first < p2.first;
    } else {
        return p1.second < p2.second;
    }
}

class Solution {
public:
    int maxEnvelopes(vector<PP>& envelopes) {
        vector<PP> &a = envelopes;
        int n = a.size();

        if (n < 2) {
            return n;
        }

        sort(a.begin(), a.end(), comp);

        vector<int> dp(n, 1);
        int i, j;
        int ans = 1;
        for (i = 1; i < n; ++i) {
            for (j = 0; j < i; ++j) {
                if (a[j].first < a[i].first && a[j].second < a[i].second) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
