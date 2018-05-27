// 1CE, 1AC, dull
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> us;
        unordered_set<int>::iterator it;
        
        while (true) {
            if (n == 1) {
                break;
            }
            if (us.find(n) == us.end()) {
                us.insert(n);
            } else {
                break;
            }
            n = dsum(n);
        }
        return n == 1;
    }
private:
    int dsum(int n) {
        int s = 0;
        int d;
        while (n > 0) {
            d = n % 10;
            n /= 10;
            s += d * d;
        }
        
        return s;
    }
};