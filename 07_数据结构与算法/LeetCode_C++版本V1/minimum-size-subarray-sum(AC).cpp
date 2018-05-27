// 1AC, O(n) solution
#include <climits>
using namespace std;

typedef long long int LL;

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
		int n = nums.size();
		int ans = INT_MAX;
		
		int ll, rr;
		LL sum = 0;
		ll = rr = 0;
		while (ll < n && rr < n) {
			sum += nums[rr++];
			if (sum <= 0) {
				ll = rr;
				sum = 0;
			} else if (sum >= s) {
				ans = min(ans, rr - ll);
				while (ll <= rr) {
					sum -= nums[ll++];
					if (ll >= rr) {
						break;
					} else if (sum >= s) {
						ans = min(ans, rr - ll);
					} else {
						break;
					}
				}
			}
		}
		
		return ans == INT_MAX ? 0 : ans;
    }
};