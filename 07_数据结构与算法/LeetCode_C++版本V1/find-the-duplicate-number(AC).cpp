class Solution {
public:
    int findDuplicate(vector<int> &nums) {
        vector<int> &a = nums;
        int n = a.size();
        int low, high, mid;
        int cnt;
        
        low = 1;
        high = a.size() - 1;
        while (low < high) {
            mid = low + (high - low) / 2;
            cnt = countRange(a, low, mid);
            if (cnt > mid - low + 1) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        
        return low;
    }
private:
    int countRange(vector<int> &v, int ll, int rr) {
        int cnt = 0;
        int n = v.size();
        int i;
        
        for (i = 0; i < n; ++i) {
            if (v[i] >= ll && v[i] <= rr) {
                ++cnt;
            }
        }
        return cnt;
    }
};