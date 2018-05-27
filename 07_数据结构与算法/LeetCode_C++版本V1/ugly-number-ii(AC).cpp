#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    Solution() {
        f.push_back(2);
        f.push_back(3);
        f.push_back(5);
        nf = f.size();
        
        idx.resize(nf, 0);
        product.resize(nf, 1);
        ans.push_back(1);
    }
    
    int nthUglyNumber(int n) {
        if (n <= 0) {
            return 0;
        }
        while (n > ans.size()) {
            calcNextUgly();
        }
        return ans[n - 1];
    }
private:
    vector<int> f;
    int nf;
    
    vector<int> idx;
    vector<int> ans;
    vector<int> product;
    
    void calcNextUgly() {
        int minProduct = INT_MAX;
        int i;
        for (i = 0; i < nf; ++i) {
            product[i] = ans[idx[i]] * f[i];
            minProduct = min(minProduct, product[i]);
        }
        ans.push_back(minProduct);
        
        for (i = 0; i < nf; ++i) {
            if (minProduct == product[i]) {
                ++idx[i];
            }
        }
    }
};