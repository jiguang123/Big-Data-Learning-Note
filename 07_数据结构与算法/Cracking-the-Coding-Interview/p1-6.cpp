// 1.6 Given an image represented by an NXN matrix, where each pixel in the image is 4 bytes, write a method to rotate the image by 90 degrees. Can you do this in place?
#include <cstdio>
#include <vector>
using namespace std;

class Solution {
public:
	void rotateImage90(vector<vector<int> > &board) {
		int n = (int)board.size();
		int i, j;
		
		if (n < 2) {
			return;
		}
		int w, h;
		int tmp;
		
		w = n / 2;
		h = n - w;
		for (i  = 0; i < w; ++i) {
			for (j = 0; j < h; ++j) {
				tmp = board[i][j];
				board[i][j] = board[n - 1 - j][i];
				board[n - 1 - j][i] = board[n - 1 - i][n - 1 - j];
				board[n - 1 - i][n - 1 - j] = board[j][n - 1 - i];
				board[j][n - 1 - i] = tmp;
			}
		}
	}
};

int main()
{
	vector<vector<int> > board;
	int i, j, n;
	Solution sol;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		board.resize(n);
		for (i = 0; i < n; ++i) {
			board[i].resize(n);
		}
		
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				scanf("%d", &board[i][j]);
			}
		}
		sol.rotateImage90(board);
		for (i = 0; i < n; ++i) {
			printf("%d", board[i][0]);
			for (j = 1; j < n; ++j) {
				printf(" %d", board[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		
		for (i = 0; i < n; ++i) {
			board[i].clear();
		}
		board.clear();
	}
	
	return 0;
}