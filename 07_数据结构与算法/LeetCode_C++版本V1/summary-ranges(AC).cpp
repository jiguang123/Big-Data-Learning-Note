// 1CE, 1AC, why not perfect?
class Solution {
public:
	vector<string> summaryRanges(vector<int>& nums) {
		vector<string> ans;
		string s;
		int i, j;
		int n = nums.size();
		
		i = 0;
		while (i < n) {
			j = i + 1;
			while (j < n && nums[j - 1] + 1 == nums[j]) {
				++j;
			}
			if (j == i + 1) {
				s = to_string(nums[i]);
			} else {
				s = to_string(nums[i]) + "->" + to_string(nums[i] + j - i - 1);
			}
			ans.push_back(s);
			i = j;
		}
		return ans;
	}
};