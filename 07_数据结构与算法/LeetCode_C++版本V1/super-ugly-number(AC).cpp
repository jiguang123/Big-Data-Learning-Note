#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int> &primes) {
        int k = primes.size();
        vector<int> v(n);
        vector<int> idx(k, 0);
        vector<int> p(k, 1);
        
        v[0] = 1;
        int i, j;
        int minp;
        for (i = 1; i < n; ++i) {
            minp = INT_MAX;
            for (j = 0; j < k; ++j) {
                p[j] = v[idx[j]] * primes[j];
                minp = min(minp, p[j]);
            }
            for (j = 0; j < k; ++j) {
                if (minp == p[j]) {
                    ++idx[j];
                }
            }
            v[i] = minp;
        }
        return v[n - 1];
    }
};