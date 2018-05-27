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
	vector<int>::iterator it;
	int n;
	int i;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		v.resize(n);
		for (i = 0; i < n; ++i) {
			scanf("%d%d", &v[i].x, &v[i].y);
		}
		sort(v.begin(), v.end());
		dp.push_back(v[0].y);
		for (i = 1; i < n; ++i) {
			if (v[i].y > dp[dp.size() - 1]) {
				dp.push_back(v[i].y);
			} else {
				it = lower_bound(dp.begin(), dp.end(), v[i].y);
				*it = v[i].y;
			}
		}
		printf("%d\n", (int)dp.size());
		
		v.clear();
		dp.clear();
	}
	
	return 0;
}