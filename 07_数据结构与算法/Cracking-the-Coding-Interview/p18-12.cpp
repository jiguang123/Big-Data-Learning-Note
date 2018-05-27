// 18.12 Given an n x n matrix, find the submatrix with largest sum. Return the sum as the result.
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	int largestSubmatrixSum (const vector<vector<int> > &matrix) {
		n = matrix.size();
		if (n == 0) {
			return 0;
		}
		m = matrix[0].size();
		if (m == 0) {
			return 0;
		}
		
		int i, j, k;
		vector<int> v;
		int msum;
		int sum;
		
		v.resize(m);
		msum = INT_MIN;
		for (i = 0; i < n; ++i) {
			fill(v.begin(), v.end(), 0);
			for (j = i; j < n; ++j) {
				for (k = 0; k < m; ++k) {
					v[k] += matrix[j][k];
				}
				sum = maxSubarraySum(v, m);
				msum = max(msum, sum);
			}
		}
		v.clear();
		return msum;
	};
private:
	int n, m;
	
	int maxSubarraySum(const vector<int> &v, int n) {
		int msum;
		int sum;
		int i;
		
		msum = INT_MIN;
		for (i = 0; i < n; ++i) {
			if (v[i] >= 0) {
				msum = max(msum, v[i]);
				break;
			}
		}
		if (i == n) {
			return msum;
		}
		
		msum = sum = 0;
		for (i = 0; i < n; ++i) {
			sum += v[i];
			msum = max(msum, sum);
			sum = max(sum, 0);
		}
		
		return msum;
	};
};

int main()
{
	int i, j;
	int n, m;
	vector<vector<int> > matrix;
	Solution sol;
	
	while (cin >> n >> m && (n > 0 && m > 0)) {
		matrix.resize(n);
		for (i = 0; i < n; ++i) {
			matrix[i].resize(m);
			for (j = 0; j < m; ++j) {
				cin >> matrix[i][j];
			}
		}
		cout << sol.largestSubmatrixSum(matrix) << endl;
		
		for (i = 0; i < n; ++i) {
			matrix[i].clear();
		}
		matrix.clear();
	}
	
	return 0;
}