// 1AC, very well, avoiding too much '/' and '%' will speed up the program.
#include <cmath>
#include <vector>
using namespace std;

class Solution {
public:
	void solveSudoku(vector<vector<char> > &board) {
		n2 = (int)board.size();
		if (n2 == 0) {
			return;
		} else if (n2 == 1) {
			board[0][0] = '1';
			return;
		}
		
		n = (int)sqrt(1.0 * n2);
		n4 = n2 * n2;
		
		int i, j;
		row.resize(n2);
		for (i = 0; i < n2; ++i) {
			row[i].resize(n2);
		}
		col.resize(n2);
		for (i = 0; i < n2; ++i) {
			col[i].resize(n2);
		}
		block.resize(n2);
		for (i = 0; i < n2; ++i) {
			block[i].resize(n2);
		}
		bc.resize(n2);
		for (i = 0; i < n2; ++i) {
			bc[i].resize(n2);
		}
		row_coordinate.resize(n4);
		col_coordinate.resize(n4);
		for (i = 0; i < n4; ++i) {
			row_coordinate[i] = i / n2;
			col_coordinate[i] = i % n2;
		}
		
		for (i = 0; i < n2; ++i) {
			for (j = 0; j < n2; ++j) {
				row[i][j] = col[i][j] = block[i][j] = 0;
			}
		}
		
		for (i = 0; i < n2; ++i) {
			for (j = 0; j < n2; ++j) {
				bc[i][j] = i / n * n + j / n;
			}
		}
		
		cc = 0;
		for (i = 0; i < n2; ++i) {
			for (j = 0; j < n2; ++j) {
				if (board[i][j] != '.') {
					// it is a digit
					row[i][board[i][j] - '1'] = 1;
					col[j][board[i][j] - '1'] = 1;
					block[bc[i][j]][board[i][j] - '1'] = 1;
				} else {
					empty_slots.push_back(i * n2 + j);
					++cc;
				}
			}
		}
		
		suc = false;
		dfs(board);
		
		// perform cleanup operations
		for (i = 0; i < n2; ++i) {
			row[i].clear();
			col[i].clear();
			block[i].clear();
			bc[i].clear();
		}
		row.clear();
		col.clear();
		block.clear();
		bc.clear();
		empty_slots.clear();
		row_coordinate.clear();
		col_coordinate.clear();
	}
private:
	bool suc;
	int n, n2, n4;
	int cc;
	vector<vector<int> > row, col, block;
	vector<vector<int> > bc;
	vector<int> empty_slots;
	vector<int> row_coordinate, col_coordinate;
	
	void dfs(vector<vector<char> > &board) {
		if (suc) {
			return;
		}
		if (cc == 0) {
			suc = true;
			return;
		}

		int r, c;
		int i;

		r = row_coordinate[empty_slots[cc - 1]];
		c = col_coordinate[empty_slots[cc - 1]];
		for (i = 0; i < n2; ++i) {
			if (row[r][i] || col[c][i] || block[bc[r][c]][i]) {
				continue;
			}
			row[r][i] = 1;
			col[c][i] = 1;
			block[bc[r][c]][i] = 1;
			empty_slots.pop_back();
			--cc;
			board[r][c] = (i + '1');
			
			dfs(board);
			if (suc) {
				return;
			}
			
			row[r][i] = 0;
			col[c][i] = 0;
			block[bc[r][c]][i] = 0;
			empty_slots.push_back(r * n2 + c);
			++cc;
			board[r][c] = '.';
		}
	}
};