// 11.6 Given an MxN matrix, each row and each column is sorted in ascending order.
// For emxample, 
// [10 19]
// [15 21]
// It doesn't mean you can expand it to a one dimensional array and still sorted.
#include <cstdio>
#include <vector>
using namespace std;

void searchMatrix(vector<vector<int> > &v, int target, int &rx, int &ry)
{
	int n, m;
	
	rx = ry = -1;
	n = (int)v.size();
	if (n == 0) {
		return;
	}
	m = (int)v[0].size();
	
	int i, j;
	
	i = 0;
	j = m - 1;
	while (i <= n - 1 && j >= 0) {
		if (target > v[i][j]) {
			++i;
		} else if (target < v[i][j]) {
			--j;
		} else {
			rx = i;
			ry = j;
			return;
		}
	}
	return;
}

int main()
{
	vector<vector<int> > v;
	int n, m;
	int i, j;
	int target;
	
	while (scanf("%d%d", &n, &m) == 2 && n > 0 && m > 0) {
		v.resize(n);
		for (i = 0; i < n; ++i) {
			v[i].resize(m);
		}
		for (i = 0; i < n; ++i) {
			for (j = 0; j < m; ++j) {
				scanf("%d", &v[i][j]);
			}
		}
		while (scanf("%d", &target) == 1) {
			searchMatrix(v, target, i, j);
			printf("(%d, %d)\n", i, j);
		}
		for (i = 0; i < n; ++i) {
			v[i].clear();
		}
		v.clear();
	}
	
	return 0;
}