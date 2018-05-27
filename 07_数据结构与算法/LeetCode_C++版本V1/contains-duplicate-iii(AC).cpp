// 3CE, 2TLE, 5WA, 1AC, I think the test cases of this problem need improvement.
// It's more tricky than it's worthy.
#include <algorithm>
#include <set>
using namespace std;

typedef long long int LL;

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, LL t) {
		if (t >= 0 && containsNearbyDuplicate(nums, k)) {
			return true;
		}
		
		++k;
		set<int> s;
		int i;
		int n = nums.size();
		if (n < 2) {
			return false;
		}
		
		k = min(k, n);
		for (i = 0; i < k; ++i) {
			s.insert(nums[i]);
		}
		
		set<int>::iterator it;
		it = s.begin();
		int v1, v2;
		while (true) {
			v1 = *it;
			++it;
			if (it == s.end()) {
				break;
			}
			v2 = *it;
			if (abs((LL)v1 - v2) <= t) {
				return true;
			}
		}
		
		while (i < n) {
			s.erase(nums[i - k]);
			s.insert(nums[i]);
			
			it = s.find(nums[i]);
			++it;
			if (it != s.end() && abs((LL)nums[i] - *it) <= t) {
				return true;
			}
			--it;
			
			if (it != s.begin()) {
				--it;
				if (abs((LL)nums[i] - *it) <= t) {
					return true;
				}
			}
			
			++i;
		}
		return false;
    }
private:
	LL abs(LL x) {
		return x > 0 ? x : -x;
	}
	
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