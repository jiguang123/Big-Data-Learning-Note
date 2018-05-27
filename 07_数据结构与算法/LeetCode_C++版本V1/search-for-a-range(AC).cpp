// 1AC, the code can be shorter, but..1AC is just fine.
class Solution {
public:
    vector<int> searchRange(int A[], int n, int target) {
        vector<int> res;
        int ll, rr, mm;
        int i1, i2;
        
        if (A == nullptr || n <= 0) {
            res.push_back(-1);
            res.push_back(-1);
            return res;
        }
        
        if (n == 1) {
            if (A[0] == target) {
                res.push_back(0);
                res.push_back(0);
            } else {
                res.push_back(-1);
                res.push_back(-1);
            }
            return res;
        }
        
        if (target < A[0] || target > A[n - 1]) {
            res.push_back(-1);
            res.push_back(-1);
            return res;
        }
        
        if (target == A[0]) {
            i1 = 0;
        } else {
            ll = 0;
            rr = n - 1;
            while (rr - ll > 1) {
                mm = (ll + rr) / 2;
                if (A[mm] < target) {
                    ll = mm;
                } else {
                    rr = mm;
                }
            }
            if (A[rr] != target) {
                res.push_back(-1);
                res.push_back(-1);
                return res;
            } else {
                i1 = rr;
            }
        }
        
        if (target == A[n - 1]) {
            i2 = n - 1;
        } else {
            ll = 0;
            rr = n - 1;
            while (rr - ll > 1) {
                mm = (ll + rr) / 2;
                if (A[mm] > target) {
                    rr = mm;
                } else {
                    ll = mm;
                }
            }
            if (A[ll] != target) {
                res.push_back(-1);
                res.push_back(-1);
                return res;
            } else {
                i2 = ll;
            }
        }
        res.push_back(i1);
        res.push_back(i2);
        return res;
    }
};