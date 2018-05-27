class Solution {
public:
    bool isUgly(int num) {
        if (num <= 0) {
            return false;
        }
        
        static const int f[] = {2, 3, 5};
        int nf = sizeof(f) / sizeof(f[0]);
        
        int i;
        for (i = 0; i < nf; ++i) {
            while (num % f[i] == 0) {
                num /= f[i];
            }
        }
        return num == 1;
    }
};