// 9.7 Implement a flood fill painter that changes a certain area to a certain color. You are given one point as the seed.
#include <cstdio>
#include <vector>
using namespace std;

void floodFill(int i, int j, int n, int m, int new_color, vector<vector<int> > &canva)
{
	int old_color = canva[i][j];

	canva[i][j] = new_color;
	if (i >= 1 && old_color == canva[i - 1][j]) {
		floodFill(i - 1, j, n, m, new_color, canva);
	}
	if (i <= n - 2 && old_color == canva[i + 1][j]) {
		floodFill(i + 1, j, n, m, new_color, canva);
	}
	if (j >= 1 && old_color == canva[i][j - 1]) {
		floodFill(i, j - 1, n, m, new_color, canva);
	}
	if (j <= m - 2 && old_color == canva[i][j + 1]) {
		floodFill(i, j + 1, n, m, new_color, canva);
	}
}

int main()
{
	int i, j, c;
	int n, m;
	vector<vector<int> > canva;
	
	scanf("%d%d", &n, &m);
	canva.resize(n);
	for (i = 0; i < n; ++i) {
		canva[i].resize(m);
	}
	
	for (i = 0; i < n; ++i) {
		for (j = 0; j < m; ++j) {
			scanf("%d", &canva[i][j]);
		}
	}
	
	while (scanf("%d%d%d", &i, &j, &c) == 3) {
		if (i >= 0 && i <= n - 1 && j >= 0 && j <= m - 1) {
			floodFill(i, j, n, m, c, canva);
		}
		for (i = 0; i < n; ++i) {
			for (j = 0; j < m; ++j) {
				printf((j == 0 ? "%d" : " %d"), canva[i][j]);
			}
			printf("\n");
		}
	}
	
	for (i = 0; i < n; ++i) {
		canva[i].clear();
	}
	canva.clear();
	
	return 0;	
}