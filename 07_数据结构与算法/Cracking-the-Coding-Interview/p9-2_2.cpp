// 9.2 How many ways are there to go from (0, 0) to (x, y), if you only go left or up, and one unit at a time?
// If some of the positions are off limits, what would you do?
#include <cstdio>
#include <vector>
using namespace std;

int main()
{
	int x, y;
	int i, j;
	vector<vector<int> > off_limits;
	vector<vector<int> > res;
	
	while (scanf("%d%d", &x, &y) == 2 && x >= 0 && y >= 0) {
		++x;
		++y;
		off_limits.resize(x);
		res.resize(x);
		for (i = 0; i < x; ++i) {
			off_limits[i].resize(y);
			res[i].resize(y);
		}
		for (i = 0; i < x; ++i) {
			for (j = 0; j < y; ++j) {
				scanf("%d", &off_limits[i][j]);
				off_limits[i][j] = !!off_limits[i][j];
				res[i][j] = 0;
			}
		}
		
		res[0][0] = off_limits[0][0] ? 0 : 1;
		for (i = 1; i < x; ++i) {
			res[i][0] = off_limits[i][0] ? 0 : res[i - 1][0];
		}
		for (j = 1; j < y; ++j) {
			res[0][j] = off_limits[0][j] ? 0 : res[0][j - 1];
		}
		for (i = 1; i < x; ++i) {
			for (j = 1; j < y; ++j) {
				res[i][j] = off_limits[i][j] ? 0 : res[i - 1][j] + res[i][j - 1];
			}
		}
		
		for (i = 0; i < x; ++i) {
			for (j = 0; j < y; ++j) {
				printf("%d ", res[i][j]);
			}
			printf("\n");
		}
		printf("%d\n", res[x - 1][y - 1]);
		
		for (i = 0; i < x; ++i) {
			off_limits[i].clear();
			res[i].clear();
		}
		off_limits.clear();
		res.clear();
	}
	
	return 0;
}