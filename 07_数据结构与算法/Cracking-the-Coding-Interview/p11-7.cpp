// 11.7 n boxes are to stack up to a tower. Every box must be strictly smaller in width and height than the one right below it.
// How many boxes at most can you stack up?
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

struct Box {
	int x;
	int y;
	Box(int _x = 0, int _y = 0): x(_x), y(_y) {};
	
	bool operator < (const Box &other) {
		if (x != other.x) {
			return x < other.x;
		} else {
			return y < other.y;
		}
	};
};

int main()
{
	vector<Box> v;
	vector<int> dp;
	int n;
	int i, j;
	int res;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		v.resize(n);
		for (i = 0; i < n; ++i) {
			scanf("%d%d", &v[i].x, &v[i].y);
		}
		sort(v.begin(), v.end());
		dp.resize(n);
		res = 0;
		for (i = 0; i < n; ++i) {
			dp[i] = 1;
			for (j = 0; j < i; ++j) {
				if (v[j].x < v[i].x && v[j].y < v[i].y) {
					dp[i] = dp[j] + 1 > dp[i] ? dp[j] + 1 : dp[i];
				}
			}
			res = dp[i] > res ? dp[i] : res;
		}
		printf("%d\n", res);
		
		v.clear();
		dp.clear();
	}
	
	return 0;
}