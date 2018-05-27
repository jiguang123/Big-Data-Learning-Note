// 1AC, nice and easy
class Solution {
public:
    int titleToNumber(string s) {
        int base = 1;
        int i;
        int len = s.length();
        int sum = 0;
        
        for (i = 0; i < len; ++i) {
            sum = sum * 26 + (s[i] - 'A');
        }
        for (i = 1; i < len; ++i) {
            base *= 26;
            sum += base;
        }
        sum += 1;
        
        return sum;
    }
};