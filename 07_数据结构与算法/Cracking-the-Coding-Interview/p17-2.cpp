// 17.2 Write an algorithm to check if someone has won the tic-tac-toe game.
// Here is the game:
//	xo-
//	ox-
//	--x
// 'x' won the game.
// Rule: anyone who gets three consecutive pieces in a row, a column or a diagonal line first wins.
#include <cstdio>
using namespace std;

int check(int a[][3])
{
	if (a == nullptr) {
		return -1;
	}
	
	int i;
	for (i = 0; i < 3; ++i) {
		if (a[i][0] == a[i][1] && a[i][1] == a[i][2] && a[i][2] != 0) {
			return a[i][2];
		}
		if (a[0][i] == a[1][i] && a[1][i] == a[2][i] && a[2][i] != 0) {
			return a[i][2];
		}
	}
	if (a[0][0] == a[1][1] && a[1][1] == a[2][2] && a[2][2] != 0) {
		return a[2][2];
	}
	if (a[0][2] == a[1][1] && a[1][1] == a[2][0] && a[2][0] != 0) {
		return a[2][2];
	}
	
	return 0;
}

int main()
{
	int a[3][3];
	int i, j;
	
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			scanf("%d", &a[i][j]);
		}
	}
	printf("%d\n", check(a));
	
	return 0;
}