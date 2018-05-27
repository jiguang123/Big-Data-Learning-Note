#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int hIndex(vector<int> &citations) {
        vector<int> &a = citations;
        sort(a.begin(), a.end());
        int low, high, mid;
        int n = a.size();
        low = 0;
        high = n;
        if (countGreaterEqual(a, high) >= high) {
            return high;
        }
        
        while (high - low > 1) {
            mid = low + (high - low) / 2;
            if (countGreaterEqual(a, mid) >= mid) {
                low = mid;
            } else {
                high = mid;
            }
        }
        return low;
    }
private:
    int countGreaterEqual(vector<int> &a, int key) {
        return a.size() - (lower_bound(a.begin(), a.end(), key) - a.begin());
    }
};