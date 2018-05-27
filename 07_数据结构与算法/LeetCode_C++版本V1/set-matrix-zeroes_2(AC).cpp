// 1WA, 1AC, use the first row and column as markers.
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

		bool c0_is_zero, r0_is_zero;
		int i, j;
		
		c0_is_zero = false;
		for (i = 0; i < n; ++i) {
			if (matrix[i][0] == 0) {
				c0_is_zero = true;
				break;
			}
		}
		
		r0_is_zero = false;
		for (i = 0; i < m; ++i) {
			if (matrix[0][i] == 0) {
				r0_is_zero = true;
				break;
			}
		}
		
		for (i = 1; i < n; ++i) {
			for (j = 1; j < m; ++j) {
				if (matrix[i][j] == 0) {
					// use 0th row and column as markers
					matrix[i][0] = 0;
					matrix[0][j] = 0;
				}
			}
		}
		
		for (i = 1; i < n; ++i) {
			if (matrix[i][0] == 0) {
				for (j = 1; j < m; ++j) {
					matrix[i][j] = 0;
				}
			}
		}
		
		for (j = 1; j < m; ++j) {
			if (matrix[0][j] == 0) {
				for (i = 1; i < n; ++i) {
					matrix[i][j] = 0;
				}
			}
		}
		
		if (r0_is_zero) {
			for (j = 0; j < m; ++j) {
				matrix[0][j] = 0;
			}
		}
		if (c0_is_zero) {
			for (i = 0; i < n; ++i) {
				matrix[i][0] = 0;
			}
		}
    }
};