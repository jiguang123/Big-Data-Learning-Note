// 1CE, 1WA, 1AC, try to make the code shorter, it'll help you understand it better.
class Solution {
public:
    vector<vector<string> > solveNQueens(int n) {
        a = nullptr;
        res.clear();
        if (n <= 0) {
            return res;
        }
        
        a = new int[n];
        solveNQueensRecursive(0, a, n);
        delete[] a;
        
        return res;
    }
private:
    int *a;
    vector<vector<string> > res;
    
    void solveNQueensRecursive(int idx, int a[], const int &n) {
        if (idx == n) {
            // one solution is found
            addSingleResult(a, n);
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
    
    void addSingleResult(const int a[], int n) {
        vector<string> single_res;
        char *str = nullptr;
        
        str = new char[n + 1];
        int i, j;
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                str[j] = '.';
            }
            str[j] = 0;
            str[a[i]] = 'Q';
            single_res.push_back(string(str));
        }
        
        res.push_back(single_res);
        single_res.clear();
        delete []str;
    }
    
    int myabs(const int x) {
        return (x >= 0 ? x : -x);
    }
};