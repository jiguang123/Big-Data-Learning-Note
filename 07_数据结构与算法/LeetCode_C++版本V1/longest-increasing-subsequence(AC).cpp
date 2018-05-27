#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int> &nums) {
        vector<int> &a = nums;
        vector<int> s;
        
        int n = a.size();
        if (n < 2) {
            return n;
        }
        
        s.push_back(a[0]);
        int i, j;
        for (i = 1; i < n; ++i) {
            if (a[i] <= s[0]) {
                s[0] = a[i];
            } else if (a[i] > s.back()) {
                s.push_back(a[i]);
            } else {
                j = lower_bound(s.begin(), s.end(), a[i]) - s.begin();
                s[j] = a[i];
            }
        }
        return (int)s.size();
    }
};