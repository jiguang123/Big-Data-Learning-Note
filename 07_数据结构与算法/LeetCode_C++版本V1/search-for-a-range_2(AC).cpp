// 1AC, very smooth.
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> searchRange(int A[], int n, int target) {
        vector<int> res;
        
        res.push_back(-1);
        res.push_back(-1);
        if (A == nullptr) {
            return res;
        }
        
        int *px, *py;
        int ix, iy;
        
        px = lower_bound(A, A + n, target);
        ix = px - A;
        if (ix >= n || A[ix] != target) {
            // not found
            return res;
        }
        
        py = upper_bound(A, A + n, target);
        --py;
        iy = py - A;
        res[0] = ix;
        res[1] = iy;
        
        return res;
    }
};