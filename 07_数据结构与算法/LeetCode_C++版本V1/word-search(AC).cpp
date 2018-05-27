// 1CE, 1AC, very smooth.
class Solution {
public:
    bool exist(vector<vector<char> > &board, string word) {
		n = (int)board.size();
		if (n == 0) {
			return false;
		}
		m = (int)board[0].size();
		word_len = (int)word.length();
		
		if (word_len == 0) {
			return true;
		}
		
		int i, j;
		for (i = 0; i < n; ++i) {
			for (j = 0; j < m; ++j) {
				if(dfs(board, word, i, j, 0)) {
					return true;
				}
			}
		}
		return false;
    }
private:
	int n, m;
	int word_len;
	
	bool dfs(vector<vector<char> > &board, string &word, int x, int y, int idx) {
		if (x < 0 || x > n - 1 || y < 0 || y > m - 1) {
			return false;
		}
		
		if (board[x][y] < 'A' || board[x][y] != word[idx]) {
			// already searched here
			// letter mismatch here
			return false;
		}
		
		bool res;
		if (idx == word_len - 1) {
			// reach the end of word, success
			return true;
		} else {
			// up
			board[x][y] -= 'A';
			res = dfs(board, word, x - 1, y, idx + 1);
			board[x][y] += 'A';
			if (res) {
				return true;
			}
			
			// down
			board[x][y] -= 'A';
			res = dfs(board, word, x + 1, y, idx + 1);
			board[x][y] += 'A';
			if (res) {
				return true;
			}
			
			// left
			board[x][y] -= 'A';
			res = dfs(board, word, x, y - 1, idx + 1);
			board[x][y] += 'A';
			if (res) {
				return true;
			}
			
			// right
			board[x][y] -= 'A';
			res = dfs(board, word, x, y + 1, idx + 1);
			board[x][y] += 'A';
			if (res) {
				return true;
			}
		}
		// all letters will be within [A-Z], thus I marked a position as 'searched' by setting them to an invalid value.
		// we have to restore the value when the DFS is done, so their values must still be distiguishable.
		// therefore, I used an offset value of 'A'.
		// this tricky way is to save the extra O(n * m) space needed as marker array.
		
		return false;
	}
};