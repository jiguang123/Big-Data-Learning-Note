// 1AC, O(n) solution with O(n) space
class Solution {
public:
    int maxProduct(int A[], int n) {
        vector<int> mm, MM;
        int i;
        
        mm.resize(n);
        MM.resize(n);
        
        mm[0] = MM[0] = A[0];
        for (i = 1; i < n; ++i) {
            mm[i] = min(A[i], min(A[i] * mm[i - 1], A[i] * MM[i - 1]));
            MM[i] = max(A[i], max(A[i] * mm[i - 1], A[i] * MM[i - 1]));
        }
        
        int ans = MM[0];
        for (i = 1; i < n; ++i) {
            ans = max(ans, MM[i]);
        }
        
        return ans;
    }
private:
    int max(const int &x, const int &y) {
        return (x > y ? x : y);
    }
    
    int min(const int &x, const int &y) {
        return (x < y ? x : y);
    }
};