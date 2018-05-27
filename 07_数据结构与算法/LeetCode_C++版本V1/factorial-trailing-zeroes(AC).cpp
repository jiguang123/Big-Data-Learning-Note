// 1AC, log5(N)
class Solution {
public:
    int trailingZeroes(int n) {
        int sum;
        
        sum = 0;
        while (n > 0) {
            sum += n / 5;
            n /= 5;
        }
        
        return sum;
    }
};