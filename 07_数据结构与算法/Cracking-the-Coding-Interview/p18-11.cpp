// 18.11 Given an NxN matrix of 0s and 1s, find out a subsquare whose all four borders are all 1s. If multiple satisfies the condition, any one is OK.
// I'll return the size and the left top corner of the subsquare.
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	void maxSubsquare(const vector<vector<int> > &matrix, int &max_left, int &max_top, int &max_size) {
		int n = matrix.size();
		
		max_left = max_top = max_size = -1;
		
		if (n <= 1) {
			return;
		}
		
		vector<vector<int> > top   (n, vector<int>(n));
		vector<vector<int> > bottom(n, vector<int>(n));
		vector<vector<int> > left  (n, vector<int>(n));
		vector<vector<int> > right (n, vector<int>(n));
		
		int i, j;
		int tmp;
		
		// use DP to preprocess the data, count how many consecutive 1s are there to the left, right, top, bottom of matrix[i][j].
		for (i = 0; i <= n - 1; ++i) {
			tmp = 0;
			for (j = 0; j <= n - 1; ++j) {
				left[i][j] = matrix[i][j] ? (++tmp) : (tmp = 0);
			}
		}
		for (j = 0; j <= n - 1; ++j) {
			tmp = 0;
			for (i = 0; i <= n - 1; ++i) {
				top[i][j] = matrix[i][j] ? (++tmp) : (tmp = 0);
			}
		}
		for (i = n - 1; i >= 0; --i) {
			tmp = 0;
			for (j = n - 1; j >= 0; --j) {
				right[i][j] = matrix[i][j] ? (++tmp) : (tmp = 0);
			}
		}
		for (j = n - 1; j >= 0; --j) {
			tmp = 0;
			for (i = n - 1; i >= 0; --i) {
				bottom[i][j] = matrix[i][j] ? (++tmp) : (tmp = 0);
			}
		}
		
		int len;
		// O(n ^ 3) solution with O(n ^ 2) space usage.
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				for (len = 2; len + i <= n && len + j <= n; ++len) {
					if (right[i][j] < len || bottom[i][j] < len) {
						continue;
					}
					if (left[i][j + len - 1] < len || bottom[i][j + len - 1] < len) {
						continue;
					}
					if (right[i + len - 1][j] < len || top[i + len - 1][j] < len) {
						continue;
					}
					if (left[i + len - 1][j + len - 1] < len || top[i + len - 1][j + len - 1] < len) {
						continue;
					}
					// all four borders are '1's.
					if (len > max_size) {
						max_top = i;
						max_left = j;
						max_size = len;
					}
				}
			}
		}
		
		// clear up data
		for (i = 0; i < n; ++i) {
			left[i].clear();
			right[i].clear();
			top[i].clear();
			bottom[i].clear();
		}
		left.clear();
		right.clear();
		top.clear();
		bottom.clear();
	};
};

int main()
{
	int n;
	int i, j;
	vector<vector<int> > matrix;
	Solution sol;
	int max_left, max_top, max_size;
	
	while (cin >> n && n > 0) {
		matrix.resize(n);
		for (i = 0; i < n; ++i) {
			matrix[i].resize(n);
		}
		
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				cin >> matrix[i][j];
			}
		}
		
		sol.maxSubsquare(matrix, max_left, max_top, max_size);
		if (max_size > 0) {
			cout << max_top << ' ' << max_left << endl;
			cout << max_top << ' ' << max_left + max_size - 1 << endl;
			cout << max_top + max_size - 1 << ' ' << max_left << endl;
			cout << max_top + max_size - 1 << ' ' << max_left + max_size - 1 << endl;
		} else {
			cout << "No subsquare found." << endl;
		}
		
		for (i = 0; i < n; ++i) {
			matrix[i].clear();
		}
		matrix.clear();
	}
	
	return 0;
}