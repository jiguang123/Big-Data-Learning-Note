#include <algorithm>
#include <stack>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
        vector<int> &a = height;
        stack<int> val, pos;
        int n = a.size();
        int i, min_i;
        int ans = 0;
        
        for (i = 0; i < n; ++i) {
            if (val.empty() || a[i] >= val.top()) {
                val.push(a[i]);
                pos.push(i);
                continue;
            }
            min_i = i;
            while (!val.empty() && val.top() > a[i]) {
                ans = max(ans, val.top() * (i - pos.top()));
                min_i = pos.top();
                val.pop();
                pos.pop();
            }
            val.push(a[i]);
            pos.push(min_i);
        }
        while (!val.empty()) {
            ans = max(ans, val.top() * (i - pos.top()));
            val.pop();
            pos.pop();
        }
        
        return ans;
    }
};