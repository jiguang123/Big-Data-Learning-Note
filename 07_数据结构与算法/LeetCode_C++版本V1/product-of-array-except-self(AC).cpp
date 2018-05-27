class Solution {
public:
    vector<int> productExceptSelf(vector<int> &nums) {
        vector<int> &a = nums;
        int n = a.size();
        vector<int> ans(n, 1);
        if (n == 0) {
            return ans;
        }
        
        int i;
        int sum = 1;
        for (i = 0; i <= n - 1; ++i) {
            ans[i] *= sum;
            sum *= a[i];
        }
        sum = 1;
        for (i = n - 1; i >= 0; --i) {
            ans[i] *= sum;
            sum *= a[i];
        }
    }
};