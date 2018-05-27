// 2WA, 1AC, moore voting
#include <climits>
using namespace std;

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> ans;
        vector<int> &a = nums;
        int n = a.size();
        if (n == 0) {
            return ans;
        }
        
        int i;
        int a1, a2;
        int c1, c2;
        
        a1 = a2 = 0;
        c1 = c2 = 0;
        for (i = 0; i < n; ++i) {
            if (a1 == a[i]) {
                ++c1;
            } else if (a2 == a[i]) {
                ++c2;
            } else if (c1 == 0) {
                a1 = a[i];
                c1 = 1;
            } else if (c2 == 0) {
                a2 = a[i];
                c2 = 1;
            } else {
                --c1;
                --c2;
            }
        }
        c1 = c2 = 0;
        for (i = 0; i < n; ++i) {
            if (a1 == a[i]) {
                ++c1;
            } else if (a2 == a[i]) {
                ++c2;
            }
        }
        if (c1 > n / 3) {
            ans.push_back(a1);
        }
        if (c2 > n / 3) {
            ans.push_back(a2);
        }
        return ans;
    }
};