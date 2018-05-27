// 2CE, 1MLE, 1RE, 1AC, trial and error
#include <cstring>
using namespace std;

const int N = 2000000;
int b[N + 1], c[N + 1];
bool once = false;

class Solution {
public:
    Solution() {
        Eratosthenes();
    }
    
    int countPrimes(int n) {
        return n > 0 ? c[n - 1] : 0;
    }
private:
    void Eratosthenes() {
        if (once) {
            return;
        }
        
        int i, j;
        
        memset(b, 0, (N + 1) * sizeof(int));
        memset(c, 0, (N + 1) * sizeof(int));
        b[0] = b[1] = 1;
        for (i = 2; i <= N / i; ++i) {
            if (b[i]) {
                continue;
            }
            for (j = i; j <= N / i; ++j) {
                b[i * j] = 1;
            }
        }
        for (i = 1; i <= N; ++i) {
            c[i] = b[i] ? c[i - 1] : c[i - 1] + 1;
        }
        once = true;
    }
};