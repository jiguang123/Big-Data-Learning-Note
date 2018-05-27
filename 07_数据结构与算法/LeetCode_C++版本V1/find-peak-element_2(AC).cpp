// 2WA, 1AC, the O(log(n)) solution
class Solution {
public:
    int findPeakElement(vector<int> &nums) {
        int n = nums.size();
        if (n == 1) {
            return 0;
        }
        
        int ll, rr, mm;
        
        ll = 0;
        rr = n - 1;
        while (rr - ll >= 2) {
            mm = (ll + rr) / 2;
            if (nums[mm] > nums[mm - 1] && nums[mm] > nums[mm + 1]) {
                return mm;
            } else if (nums[mm - 1] < nums[mm]) {
                ll = mm;
            } else {
                rr = mm;
            }
        }
        if (nums[0] > nums[1]) {
            return 0;
        } else {
            return n - 1;
        }
    }
};