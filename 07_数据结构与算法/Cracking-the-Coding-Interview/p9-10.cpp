// 9.10 A stack of n boxes is form a tower. where every stack must be strictly larger than the one right above it.
// The boxes cannot be rotated.
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

struct Box {
	// width
	int w;
	// height
	int h;
	// depth
	int d;
	Box(int _w = 0, int _h = 0, int _d = 0): w(_w), h(_h), d(_d) {};
	
	bool operator < (const Box &other) {
		if (w != other.w) {
			return w < other.w;
		} else if (h != other.h) {
			return h < other.h;
		} else {
			return d < other.d;
		}
	};
};

int main()
{
	int n, i, j;
	Box box;
	vector<Box> v;
	vector<int> dp;
	int result;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		v.resize(n);
		for (i = 0; i < n; ++i) {
			scanf("%d%d%d", &v[i].w, &v[i].h, &v[i].d);
		}
		sort(v.begin(), v.end());
		dp.resize(n);
		for (i = 0; i < n; ++i) {
			dp[i] = v[i].h;
		}
		for (i = 0; i < n; ++i) {
			for (j = 0; j < i; ++j) {
				if (v[i].w > v[j].w && v[i].h > v[j].h && v[i].d > v[j].d) {
					dp[i] = v[i].h + dp[j] > dp[i] ? v[i].h + dp[j] : dp[i];
				}
			}
		}
		result = dp[0];
		for (i = 1; i < n; ++i) {
			result = dp[i] > result ? dp[i] : result;
		}
		v.clear();
		dp.clear();
		printf("%d\n", result);
	}
	
	return 0;
}