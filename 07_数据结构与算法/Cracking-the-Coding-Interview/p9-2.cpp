// 9.2 How many ways are there to go from (0, 0) to (x, y), if you only go left or up, and one unit at a time?
#include <cstdio>
using namespace std;

int combination(int n, int k)
{
	if (n < k) {
		return 0;
	} else if (n == 0) {
		return 0;
	} else if (k > n / 2) {
		return combination(n, n - k);
	}

	int i;
	int res, div;
	
	res = div = 1;
	for (i = 1; i <= k; ++i) {
		res *= (n + 1 - i);
		div *= i;
		if (res % div == 0) {
			res /= div;
			div = 1;
		}
	}
	if (res % div == 0) {
		res /= div;
		div = 1;
	}
	
	return res;
}

int main()
{
	int x, y;
	
	while (scanf("%d%d", &x, &y) == 2 && x >= 0 && y >= 0) {
		printf("%d\n", combination(x + y, x));
	}
	
	return 0;
}