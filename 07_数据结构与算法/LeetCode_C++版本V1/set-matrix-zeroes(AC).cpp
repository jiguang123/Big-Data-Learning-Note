// 1AC, O(m + n) solution.
class Solution {
public:
    void setZeroes(vector<vector<int> > &matrix) {
		int n, m;
		
		n = matrix.size();
		if (n == 0) {
			return;
		}
		m = matrix[0].size();
		if (m == 0) {
			return;
		}

		int i, j;
		vector<int> row_zero, col_zero;
		
		for (i = 0; i < n; ++i) {
		    row_zero.push_back(0);
		}
		for (j = 0; j < m; ++j) {
		    col_zero.push_back(0);
		}
		
		for (i = 0; i < n; ++i) {
			for (j = 0; j < m; ++j) {
				if (matrix[i][j] == 0) {
					row_zero[i] = 1;
					col_zero[j] = 1;
				}
			}
		}
		
		for (i = 0; i < n; ++i) {
			if (row_zero[i]) {
				for (j = 0; j < m; ++j) {
					matrix[i][j] = 0;
				}
			}
		}
		
		for (j = 0; j < m; ++j) {
			if (col_zero[j]) {
				for (i = 0; i < n; ++i) {
					matrix[i][j] = 0;
				}
			}
		}
		
		row_zero.clear();
		col_zero.clear();
    }
};