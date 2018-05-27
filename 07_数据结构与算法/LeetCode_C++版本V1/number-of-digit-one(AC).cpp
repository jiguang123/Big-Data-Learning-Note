// 1AC, lucky enough
#include <vector>
using namespace std;

typedef long long int LL;
class Solution {
public:
    Solution() {
        LL b10 = 1;
        s.push_back(0);
        s.push_back(1);
        int i;
        for (i = 2; i <= N; ++i) {
            b10 *= 10;
            s.push_back(10 * s.back() + b10);
        }
    }
    
    int countDigitOne(int n) {
        if (n < 1) {
            return 0;
        }
        if (n < 10) {
            return 1;
        }
        LL b10 = 1;
        int i = 0;
        while (b10 * 10 <= n) {
            b10 *= 10;
            ++i;
        }
        int d = n / b10;
        if (d > 1) {
            return b10 + d * s[i] + countDigitOne(n % b10);
        } else {
            return (n % b10 + 1) + d * s[i] + countDigitOne(n % b10);
        }
    }
private:
    static const int N = 18;
    vector<LL> s;
};