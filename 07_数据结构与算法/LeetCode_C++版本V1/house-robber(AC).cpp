// 1WA, 1AC, O(1) space.
#include <algorithm>
using namespace std;

class Solution {
public:
    int rob(vector<int> &num) {
        int n = num.size();
        int i;
        
        if (n == 0) {
            return 0;
        } else if (n == 1) {
            return num[0];
        } else if (n == 2) {
            return max(num[0], num[1]);
        }
        
        int ans;
        
        ans = max(num[0], num[1]);
        num[2] = num[0] + num[2];
        ans = max(ans, num[2]);
        for (i = 3; i < n; ++i) {
            num[i] = max(num[i - 2], num[i - 3]) + num[i];
            ans = max(ans, num[i]);
        }
        
        return ans;
    }
};