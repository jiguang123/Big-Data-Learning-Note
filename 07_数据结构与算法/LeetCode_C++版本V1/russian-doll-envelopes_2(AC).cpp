// Optimized with binary search, O(n * log(n))
#include <algorithm>
#include <climits>
using namespace std;

typedef pair<int, int> PP;
bool comp(const PP &p1, const PP &p2)
{
    if (p1.first != p2.first) {
        return p1.first < p2.first;
    } else {
        // Think about why
        return p1.second > p2.second;
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

        vector<int> seq(n, INT_MAX);
        int i, j;
        int ans = 1;
        
        for (i = 0; i < n; ++i) {
            j = lower_bound(seq.begin(), seq.end(), a[i].second) - seq.begin();
            seq[j] = a[i].second;
            ans = max(ans, j + 1);
        }
        return ans;
    }
};
