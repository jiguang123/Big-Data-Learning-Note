// 1.7 Write an algorithm such that if an element in an MxN matrx is 0, its antire row and column are set to 0.
#include <cstdio>
#include <vector>
using namespace std;

class Solution {
public:
	void setMatrixZero(vector<vector<int> > &board) {
		int m, n;
		
		m = (int)board.size();
		if (m == 0) {
			return;
		}
		n = (int)board[0].size();
		if (n == 0) {
			return;
		}
		
		int i, j;
		bool row0_has_zero = false;
		bool col0_has_zero = false;
		for (i = 0; i < m; ++i) {
			if (board[i][0] == 0) {
				col0_has_zero = true;
				break;
			}
		}
		for (j = 0; j < n; ++j) {
			if (board[0][j] == 0) {
				row0_has_zero = true;
			}
		}
		for (i = 1; i < m; ++i) {
			for (j = 1; j < n; ++j) {
				if (board[i][j] == 0) {
					board[i][0] = 0;
					board[0][j] = 0;
				}
			}
		}
		for (i = 1; i < m; ++i) {
			if (board[i][0] == 0) {
				for (j = 1; j < n; ++j) {
					board[i][j] = 0;
				}
			}
		}
		for (j = 1; j < n; ++j) {
			if (board[0][j] == 0) {
				for (i = 1; i < m; ++i) {
					board[i][j] = 0;
				}
			}
		}
		if (row0_has_zero) {
			for (j = 0; j < n; ++j) {
				board[0][j] = 0;
			}
		}
		if (col0_has_zero) {
			for (i = 0; i < m; ++i) {
				board[i][0] = 0;
			}
		}
	}
};

int main()
{
	vector<vector<int> > board;
	int i, j;
	int m, n;
	Solution sol;
	
	while (scanf("%d%d", &m, &n) == 2 && (m || n)) {
		board.resize(m);
		for (i = 0; i < m; ++i) {
			board[i].resize(n);
		}
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j) {
				scanf("%d", &board[i][j]);
			}
		}
		sol.setMatrixZero(board);
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j) {
				if (j > 0) {
					printf(" %d", board[i][j]);
				} else {
					printf("%d", board[i][j]);
				}
			}
			printf("\n");
		}
		printf("\n");
	}
	
	return 0;
}