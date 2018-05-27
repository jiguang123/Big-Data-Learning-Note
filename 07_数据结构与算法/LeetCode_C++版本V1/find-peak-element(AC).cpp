// 1CE, 2WA, 1AC, how to achieve logN with unordered data?
class Solution {
public:
    int findPeakElement(const vector<int> &num) {
        int n = (int)num.size();

        if (n == 1) {
            return 0;
        }
        
        if (num[0] > num[1]) {
            return 0;
        }
        
        if (num[n - 1] > num[n - 2]) {
            return n - 1;
        }
        
        int i;
        for (i = 1; i < n - 1; ++i) {
            if (num[i] > num[i - 1] && num[i] > num[i + 1]) {
                return i;
            }
        }
    }
};