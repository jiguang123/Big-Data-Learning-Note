class Solution {
public:
    vector<int> singleNumber(vector<int> &nums) {
        vector<int> &a = nums;
        
        int i;
        int n = a.size();
        int sum = 0;
        for (i = 0; i < n; ++i) {
            sum ^= a[i];
        }
        sum = sum & -sum;
        int s1, s2;
        s1 = s2 = 0;
        for (i = 0; i < n; ++i) {
            if (a[i] & sum) {
                s1 ^= a[i];
            } else {
                s2 ^= a[i];
            }
        }
        vector<int> ans;
        
        ans.push_back(s1);
        ans.push_back(s2);
        
        return ans;
    }
};