// 2WA, 1AC, O(n) solution with O(n) space
#include <algorithm>
using namespace std;

class Solution {
public:
    int rob(vector<int> &num) {
		int n = num.size();
		if (n == 1) {
			return num[0];
		}
		int i;
		int ans = 0;
		vector<int> v;
		
		for (i = 0; i < n - 1; ++i) {
			v.push_back(num[i]);
		}
		ans = solve(v);
		
		v.clear();
		for (i = 1; i < n; ++i) {
			v.push_back(num[i]);
		}
		ans = max(ans, solve(v));
		
        return ans;
    }
private:
	int solve(vector<int> &num) {
        int n = num.size();
        if (n == 0) {
            return 0;
        } else if (n == 1) {
            return num[0];
        } else if (n == 2) {
            return max(num[0], num[1]);
        }
		
        int ans = max(num[0], num[1]);
        num[2] = num[0] + num[2];
        ans = max(ans, num[2]);
        int i;
        for (i = 3; i < n; ++i) {
            num[i] = max(num[i - 2], num[i - 3]) + num[i];
            ans = max(ans, num[i]);
        }
		
		return ans;
	}
};