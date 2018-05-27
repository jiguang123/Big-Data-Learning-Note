// 5CE, 2WA, 1AC, "const int &x", constant value has no reference.
class Solution {
public:
    int trap(int A[], int n) {
        if (A == nullptr || n < 3) {
            return 0;
        }
        
        vector<int> vl(n), vr(n);
        int i;
        int max_val;
        int result;
        
        max_val = 0;
        for (i = 0; i <= n - 1; ++i) {
            vl[i] = max_val;
            max_val = mymax(max_val, A[i]);
        }
        max_val = 0;
        for (i = n - 1; i >= 0; --i) {
            vr[i] = max_val;
            max_val = mymax(max_val, A[i]);
        }
        
        result = 0;
        for (i = 0; i < n; ++i) {
            max_val = mymax(0, mymin(vl[i], vr[i]) - A[i]);
            result += max_val;
        }
        vl.clear();
        vr.clear();
        
        return result;
    }
private:
    int mymin(const int x, const int y) {
        return (x < y ? x : y);
    }
    
    int mymax(const int x, const int y) {
        return (x > y ? x : y);
    }
};