// 3CE, 1AC, why so hasty?
class Solution {
public:
    int totalNQueens(int n) {
        a = nullptr;
        if (n <= 0) {
            return 0;
        }
        
		res_count = 0;
        a = new int[n];
        solveNQueensRecursive(0, a, n);
        delete[] a;
        
        return res_count;
    }
private:
    int *a;
    int res_count;
    
    void solveNQueensRecursive(int idx, int a[], const int &n) {
        if (idx == n) {
            // one solution is found
            ++res_count;
            return;
        }
        
        int i, j;
        // check if the current layout is valid.
        for (i = 0; i < n; ++i) {
            a[idx] = i;
            for (j = 0; j < idx; ++j) {
                if (a[j] == a[idx] || myabs(idx - j) == myabs(a[idx] - a[j])) {
                    break;
                }
            }
            if (j == idx) {
                // valid layout.
                solveNQueensRecursive(idx + 1, a, n);
            }
        }
    }
    
    int myabs(const int x) {
        return (x >= 0 ? x : -x);
    }
};