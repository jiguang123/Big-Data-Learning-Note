class Solution {
public:
    int uniquePaths(int m, int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if(m > n){
            return uniquePaths(n, m);
        }
        
        // 1WA here, integer overflow
        long long int sum, res;
        
        // 1WA here, m and n start from 0, not 1
        --m;
        --n;
        sum = res = 1;
        // 1CE here, int i is not declared
        for(int i = 1; i <= m; ++i){
            sum *= i;
            res *= (m + n + 1 - i);
            if(res % sum == 0){
                res /= sum;
                sum = 1;
            }
        }
        
        return res;
    }
};