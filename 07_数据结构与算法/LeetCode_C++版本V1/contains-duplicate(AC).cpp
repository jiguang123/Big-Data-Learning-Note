// 1AC, hashing
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int> &nums) {
		unordered_set<int> us;
		
		int i, n = nums.size();
		for (i = 0; i < n; ++i) {
			if (us.find(nums[i]) != us.end()) {
				return true;
			}
			us.insert(nums[i]);
		}
		return false;
    }
};