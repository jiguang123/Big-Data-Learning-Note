// 1CE, 1AC, good.
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxArea(vector<int> &height) {
		if (height.empty()) {
			return 0;
		}
		
		int ll, rr, kk, result;
		
		ll = 0;
		rr = (int)height.size() - 1;
		result = 0;
		while (ll < rr) {
			result = max(result, min(height[ll], height[rr]) * (rr - ll));
			if (height[ll] < height[rr]) {
				kk = ll + 1;
				while (kk < rr && height[kk] <= height[ll]) {
					++kk;
				}
				ll = kk;
			} else {
				kk = rr - 1;
				while (kk > ll && height[kk] <= height[rr]) {
					--kk;
				}
				rr = kk;
			}
		}
		
        return result;
    }
};