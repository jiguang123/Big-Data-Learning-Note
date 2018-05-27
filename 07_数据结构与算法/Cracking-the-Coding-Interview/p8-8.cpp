// 8.8 Othello game, the rule is balabala. Try to design a class to play the game.
// Here are the rules:
//	1. two players, one black, one white, play alternatively, black first.
//	2. the board is 8x8, two blacks and two whites are placed in the center first.
// 00000000
// 00000000
// 00000000
// 000bw000
// 000wb000
// 00000000
// 00000000
// 00000000
//	3. every time, a player has to place a piece on an empty position, if the eight directions have the player's pieces, then all the opponent's pieces trapped between those pieces and the new piece is flipped to the current player.
//	4. for every move, the player must at least flip one of the opponent's pieces.
//	5. if a player is unable to make a move, the game ends. Whoever has more pieces on the board wins.
#include <cstdio>
#include <vector>
using namespace std;

class OthelloGame {
public:
	OthelloGame() {
		board.resize(8);
		possible_position.resize(8);
		int i, j;
		for (i = 0; i < 8; ++i) {
			board[i].resize(8);
			possible_position[i].resize(8);
		}
		for (i = 0; i < 8; ++i) {
			for (j = 0; j < 8; ++j) {
				board[i][j] = 0;
			}
		}
		board[3][3] = board[4][4] = 1;
		board[3][4] = board[4][3] = 2;
		winner = 0;
		
		dd[0][0] = -1;
		dd[0][1] = -1;
		dd[1][0] = -1;
		dd[1][1] = 0;
		dd[2][0] = -1;
		dd[2][1] = +1;
		dd[3][0] = 0;
		dd[3][1] = -1;
		dd[4][0] = 0;
		dd[4][1] = +1;
		dd[5][0] = +1;
		dd[5][1] = -1;
		dd[6][0] = +1;
		dd[6][1] = 0;
		dd[7][0] = +1;
		dd[7][1] = +1;
	};
	
	bool playGame() {
		int i, j;
		int x, y;
		int current_player;
		int pc[2];
		
		current_player = 1;
		while (!winner) {
			if (!checkPositions(current_player)) {
				pc[0] = pc[1] = 0;
				for (i = 0; i < 8; ++i) {
					for (j = 0; j < 8; ++j) {
						if (board[i][j]) {
							++pc[board[i][j] - 1];
						}
					}
				}
				winner = (pc[0] > pc[1] ? 1 : pc[0] < pc[1] ? 2 : 0);
				break;
			}
			while (true) {
				printBoard();
				printf("Player %d please move: ", current_player);
				scanf("%d%d", &x, &y);
				if (inBound(x, y) && possible_position[x][y]) {
					setPiece(x, y, current_player);
					current_player = (current_player == 1) ? 2 : 1;
					break;
				} else {
					printf("Invalid move.\n");
				}
			}
		}
		return 0;
	};
	
	~OthelloGame() {
		int i;
		
		for (i = 0; i < 8; ++i) {
			board[i].clear();
			possible_position[i].clear();
		}
		board.clear();
		possible_position.clear();
	}
private:
	// 1 for player one, 2 for player two, 0 for empty.
	vector<vector<int> > board;
	vector<vector<int> > possible_position;
	int dd[8][2];
	int winner;
	
	void printBoard() {
		int i, j;
		putchar(' ');
		putchar(' ');
		for (i = 0; i < 8; ++i) {
			putchar('0' + i);
			putchar(' ');
		}
		puts("                  \n");
		for (i = 0; i < 8; ++i) {
			putchar('0' + i);
			putchar(' ');
			for (j = 0; j < 8; ++j) {
				putchar('0' + board[i][j]);
				putchar(' ');
			}
			putchar('\n');
		}
	};
	
	bool inBound(int x, int y) {
		return x >= 0 && x <= 7 && y >= 0 && y <= 7;
	};
	
	bool checkPositions(int current_player) {
		int i, j, k;
		int x, y;
		int len;
		int count;
		
		for (i = 0; i < 8; ++i) {
			for (j = 0; j < 8; ++j) {
				possible_position[i][j] = 0;
			}
		}
		count = 0;
		
		for (i = 0; i < 8; ++i) {
			for (j = 0; j < 8; ++j) {
				if (board[i][j]) {
					continue;
				}
				for (k = 0; k < 8; ++k) {
					len = 1;
					while (true) {
						x = i + len * dd[k][0];
						y = j + len * dd[k][1];
						if (!inBound(x, y)) {
							break;
						}
						if (board[x][y] == 0) {
							break;
						} else if (board[x][y] == current_player) {
							if (len > 1) {
								possible_position[i][j] = 1;
								++count;
							}
							break;
						} else {
							++len;
						}
					}
					if (possible_position[i][j]) {
						break;
					}
				}
			}
		}
		
		return count > 0;
	};
	
	void setPiece(int x, int y, int current_player) {
		int xx, yy;
		int k;
		int len;
		
		board[x][y] = current_player;
		for (k = 0; k < 8; ++k) {
			len = 1;
			while (true) {
				xx = x + len * dd[k][0];
				yy = y + len * dd[k][1];
				if (!inBound(x, y)) {
					break;
				}
				if (board[xx][yy] == 0) {
					break;
				} else if (board[xx][yy] == current_player) {
					while (--len > 0) {
						xx = x + len * dd[k][0];
						yy = y + len * dd[k][1];
						board[xx][yy] = current_player;
					}
				} else {
					++len;
				}
			}
		}
	};
};

int main()
{
	OthelloGame game;
	
	game.playGame();
	
	return 0;
}