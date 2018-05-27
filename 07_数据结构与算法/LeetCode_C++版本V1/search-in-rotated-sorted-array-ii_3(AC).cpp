class Solution {
    /** 
     * param A : an integer ratated sorted array
     * param target :  an integer to be searched
     * return : an integer
     */
public:
    bool search(vector<int> &A, int target) {
        int n = A.size();
        int ll, rr, mm;
        
        ll = 0;
        rr = n - 1;
        while (ll <= rr) {
            if (A[ll] == target) {
                return true;
            }
            if (A[ll] == A[rr]) {
                ++ll;
                continue;
            }
            mm = ll + (rr - ll) / 2;
            if (A[mm] == target) {
                return true;
            }
            if (A[ll] < A[mm]) {
                if (target >= A[ll] && target < A[mm]) {
                    rr = mm - 1;
                } else {
                    ll = mm + 1;
                }
            } else if (A[mm] < A[rr]) {
                if (target > A[mm] && target <= A[rr]) {
                    ll = mm + 1;
                } else {
                    rr = mm - 1;
                }
            } else {
                // In case there're duplicates
                ++ll;
            }
        }
        return false;
    }
};