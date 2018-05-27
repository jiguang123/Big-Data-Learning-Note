class Solution {
public:
    int findMin(vector<int> &num) {
        int n = (int)num.size();
        
        while (n > 1 && num[0] == num[n - 1]) {
            --n;
        }
        
        if (n == 1 || num[0] < num[n - 1]) {
            return num[0];
        }
        
        int ll, mm, rr;
        
        ll = 0;
        rr = n - 1;
        while (rr - ll > 1) {
            mm = ll + (rr - ll) / 2;
            if (num[mm] >= num[ll]) {
                ll = mm;
            } else {
                rr = mm;
            }
        }
        
        return num[rr];
    }
};