// 1AC, old
class Solution {
public:
    int majorityElement(vector<int> &num) {
        int val, cnt;
        int n, i;
        
        n = (int)num.size();
        val = num[0];
        cnt = 1;
        
        for (i = 1; i < n; ++i) {
            if (val == num[i]) {
                ++cnt;
            } else if (cnt > 1) {
                --cnt;
            } else {
                val = num[i];
                cnt = 1;
            }
        }
        
        return val;
    }
};