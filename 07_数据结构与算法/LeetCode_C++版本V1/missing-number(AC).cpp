typedef long long LL;
class Solution {
public:
    int missingNumber(vector<int> &nums) {
        vector<int> &a = nums;
        LL sum = 0;
        int n = a.size();
        int i;
        for (i = 0; i < n; ++i) {
            sum += a[i];
        }
        return (1LL + n) * n / 2 - sum;
    }
};