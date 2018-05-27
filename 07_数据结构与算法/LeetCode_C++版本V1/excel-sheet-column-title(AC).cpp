// 1CE, 4WA, 1AC, so careless
class Solution {
public:
    string convertToTitle(int n) {
        long long int n1 = n;
        long long int base = 26;
        int len = 1;
        
        --n1;
        while (n1 >= base) {
            n1 -= base;
            base *= 26;
            ++len;
        }
        
        string s;
        
        base /= 26;
        while (base > 0) {
            s.push_back(n1 / base + 'A');
            n1 %= base;
            base /= 26;
        }
        
        return s;
    }
};