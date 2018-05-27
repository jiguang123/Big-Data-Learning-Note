// 3RE, 1WA, 1AC
class Solution {
public:
    double pow(double x, int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if(x == 0.0){
            return 0;
        }
        
        // 1RE here, special case of x = 1
        if(x == 1.0){
            return 1.0;
        }
        
        // 1RE, special case of x < 0
        if(x < 0){
            if(n % 2 == 1){
                return -pow(-x, n);
            }else{
                return pow(-x, n);
            }
        }
        
        // 1RE, should be $n, wrote $x
        if(n < 0){
            return pow(1.0 / x, -n);
        }else if(n == 0){
            return 1.0;
        }else if(n == 1){
            return x;
        }else{
            if(n % 2 == 1){
                // 1WA here, pow(x * x, n / 2) is wrong
                double res = pow(x, n / 2);
                return x * res * res;
            }else{
                double res = pow(x, n / 2);
                return res * res;
            }
        }
    }
};