// 6.3 Given two jugs with size x and y, and a volume v between 0 and y inclusive. Show how you're gonna get that value.
// Note that you can only fill a jug, empty a jug or pour from one into another.
// x and y will be positive and relatively prime.
#include <cstdio>
using namespace std;

int gcd(int x, int y)
{
	return x == 0 ? y : gcd(y % x, x);
}

int main()
{
	int x, y;
	int vx, vy;
	int v;
	
	while (scanf("%d%d%d", &x, &y, &v) == 3 && (x > 0 && y > 0 && v > 0)) {
		if (x > y) {
			continue;
		}
		if (gcd(x, y) > 1) {
			continue;
		}
		
		vx = 0;
		vy = y;
		printf("[%d, %d]: fill y\n", vx, vy);
		while (vy != v) {
			if (vy < x) {
				vx = vy;
				vy = 0;
				printf("[%d, %d]: pour y into x\n", vx, vy);
				vy = y;
				printf("[%d, %d]: fill y\n", vx, vy);
				vy = vy - (x - vx);
				vx = x;
				printf("[%d, %d]: pour y into x\n", vx, vy);
				vx = 0;
				printf("[%d, %d]: empty x\n", vx, vy);
			} else {
				vy -= x;
				vx = x;
				printf("[%d, %d]: pour y into x\n", vx, vy);
				vx = 0;
				printf("[%d, %d]: empty x\n", vx, vy);
			}
		}
	}
	
	return 0;
}