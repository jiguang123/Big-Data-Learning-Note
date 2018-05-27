// 1RE, 1AC, not perfect
#include <unordered_map>
using namespace std;

class Solution {
public:
	bool containsNearbyDuplicate(vector<int>& nums, int k) {
		++k;
		
		unordered_map<int, int> um;
		int n = nums.size();
		int i = 0;
		while (i < n && i < k) {
			++um[nums[i]];
			if (um[nums[i]] > 1) {
				return true;
			}
			++i;
		}
		while (i < n) {
			--um[nums[i - k]];
			++um[nums[i]];
			if (um[nums[i]] > 1) {
				return true;
			}
			++i;
		}
		return false;
	}
};