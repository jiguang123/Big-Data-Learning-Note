class Solution {
    /** 
     * param A : an integer ratated sorted array
     * param target :  an integer to be searched
     * return : an integer
     */
public:
    int search(vector<int> &A, int target) {
        int n = A.size();
        if (n == 0) {
            return -1;
        }
        
        int ll, rr, mm;
        ll = 0;
        rr = n - 1;
        int k = findRotatePos(A);
        while (ll <= rr) {
            mm = (ll + rr) / 2;
            if (target < A[(mm + k) % n]) {
                rr = mm - 1;
            } else if (target > A[(mm + k) % n]) {
                ll = mm + 1;
            } else {
                return (mm + k) % n;
            }
        }
        return -1;
    }
private:
    int findRotatePos(vector<int> &A) {
        int ll, rr, mm;
        int n = A.size();
        
        if (n <= 1) {
            return 0;
        }
        
        ll = 0;
        rr = n - 1;
        while (rr - ll > 1) {
            if (A[ll] < A[rr]) {
                break;
            }
            if (A[ll] == A[rr]) {
                --rr;
                continue;
            }
            mm = (ll + rr) / 2;
            if (A[mm] >= A[ll]) {
                ll = mm;
            } else {
                rr = mm;
            }
        }
        return A[ll] < A[rr] ? ll : rr;
    }
};