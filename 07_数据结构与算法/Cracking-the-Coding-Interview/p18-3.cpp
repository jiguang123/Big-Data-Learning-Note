// 18.3 pick m integers randomly from an array of n integer.
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

void randomSubset(const vector<int> &src, vector<int> &dst, int m)
{
	vector<int> v;
	int i, j;
	int idx;
	int n;
	
	v = src;
	n = (int)v.size();
	dst.resize(m);
	for (i = 0; i < m; ++i) {
		idx = rand() % n;
		dst[i] = v[idx];
		--n;
		for (j = idx; j < n; ++j) {
			v[j] = v[j + 1];
		}
	}
	v.clear();
}

int main()
{
	int i;
	int n, m;
	vector<int> src;
	vector<int> dst;
	int cc;
	

	cc = 0;
	while (scanf("%d%d", &n, &m) == 2) {
		++cc;
		srand((unsigned)(time(NULL) * cc));
		src.resize(n);
		for (i = 0; i < n; ++i) {
			src[i] = i;
		}
		randomSubset(src, dst, m);
		for (i = 0; i < m; ++i) {
			printf((i % 8 == 7 ? "%3d\n" : "%3d "), dst[i]);
		}
		printf("\n");
	}
	
	return 0;
}