// 7.7 Find the kth number that has no prime factors other than 3, 5 or 7.
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

int main()
{
	vector<int> v;
	int n = 0;
	int p3, p5, p7;
	int res3, res5, res7;
	int min_res;
	const int MAX = 1000000000;
	
	v.push_back(1);
	p3 = p5 = p7 = 0;
	while (true) {
		res3 = v[p3] * 3;
		res5 = v[p5] * 5;
		res7 = v[p7] * 7;
		min_res = min(res3, min(res5, res7));
		if (min_res > MAX) {
			break;
		}
		if (res3 == min_res) {
			++p3;
		}
		if (res5 == min_res) {
			++p5;
		}
		if (res7 == min_res) {
			++p7;
		}
		v.push_back(min_res);
	}
	printf("count = %u\n", v.size());
	
	while (scanf("%d", &n) == 1) {
		if (n < 0 || n >= (int)v.size()) {
			printf("Out of range.\n");
		} else {
			printf("%d\n", v[n]);
		}
	}
	
	return 0;
}