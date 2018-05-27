class Solution {
public:
    int jump(vector<int> &A) {
        int n = A.size();
        if (n < 2) {
            return 0;
        }
        int i;
        int oldr, r;
        int ans = 0;
        
        oldr = r = 0;
        i = 0;
        while (i < n) {
            if (r < i) {
                // Unreachable
                return -1;
            }
            
            if (r >= n - 1) {
                return ans;
            }
            while (i <= oldr) {
                r = max(r, i + A[i]);
                ++i;
            }
            oldr = r;
            ++ans;
        }
        return ans;
    }
};