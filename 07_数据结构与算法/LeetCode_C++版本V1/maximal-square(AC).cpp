// 2WA, 1AC, O(m * n) solution.
// It's square, not rectangle.
class Solution {
public:
	int maximalSquare(vector<vector<char> > &matrix) {
		int m = matrix.size();
		if (m == 0) {
			return 0;
		}
		int n = matrix[0].size();
		if (n == 0) {
			return 0;
		}
		
		vector<int> a;
		a.resize(n, 0);
		
		int i, j;
		int ans = 0;
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j) {
				a[j] = matrix[i][j] == '0' ? 0 : a[j] + matrix[i][j] - '0';
			}
			ans = max(ans, largestSquareArea(a));
		}
		
		return ans;
	}
private:
	int largestSquareArea(vector<int> &height) {
		int i;
		int n = height.size();
		if (n == 0) {
			return 0;
		}
		
		vector<int> ll, rr;
		int max_area = 0;
		int area = 0;
		
		ll.resize(n);
		rr.resize(n);
		for (i = 0; i < n; ++i) {
			ll[i] = i;
			rr[i] = i;
		}
		for (i = 0; i <= n - 1; ++i) {
			while (ll[i] - 1 >= 0 && height[ll[i] - 1] >= height[i]) {
				ll[i] = ll[ll[i] - 1];
			}
		}
		for (i = n - 1; i >= 0; --i) {
			while (rr[i] + 1 <= n - 1 && height[rr[i] + 1] >= height[i]) {
				rr[i] = rr[rr[i] + 1];
			}
		}
		
		int len;
		for (i = 0; i < n; ++i) {
			len = min(rr[i] - ll[i] + 1, height[i]);
			area = len * len;
			if (area > max_area) {
				max_area = area;
			}
		}
		
		ll.clear();
		rr.clear();
		return max_area;
	}
};