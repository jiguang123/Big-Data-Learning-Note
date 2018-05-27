// 1AC, not an O(n) solution, though, one not yet come up with...
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximumGap(vector<int> &num) {
        sort(num.begin(), num.end());
        int n;
        
        n = (int)num.size();
        if (n < 2) {
            return 0;
        }
        
        int i;
        int ans = abs(num[0] - num[1]);
        for (i = 2; i < n; ++i) {
            ans = max(ans, abs(num[i - 1] - num[i]));
        }
        
        return ans;
    }
private:
    int max(const int &x, const int &y) {
        return x > y ? x : y;
    }
    
    int abs(const int &x) {
        return x >= 0 ? x : -x;
    }
};