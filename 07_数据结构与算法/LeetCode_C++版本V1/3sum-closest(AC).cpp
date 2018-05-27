// 2TLE, 1AC, O(n^2) solution, linear scan is faster than binary search.
#include <algorithm>
using namespace std;

class Solution {
public:
	int threeSumClosest(vector<int> &num, int target) {
		int n = (int)num.size();
		if (n < 3) {
			return 0;
		}
		
		int i, j, k;
		int res;
		int sum;
		
		// sort the array for linear scan
		sort(num.begin(), num.end());
		// intialize with whatever result here
		res = num[0] + num[1] + num[2];
		for (i = 0; i < n; ++i) {
			j = i + 1;
			k = n - 1;
			while (j < k) {
				sum = num[i] + num[j] + num[k];
				if (sum < target) {
					++j;
					if (myabs(sum - target) < myabs(res - target)) {
						res = sum;
					}
				} else if (sum > target) {
					--k;
					if (myabs(sum - target) < myabs(res - target)) {
						res = sum;
					}
				} else {
					return target;
				}
			}
		}
		
		return res;
	}
private:
	int myabs(const int n) {
		return (n >= 0 ? n : -n);
	}
};