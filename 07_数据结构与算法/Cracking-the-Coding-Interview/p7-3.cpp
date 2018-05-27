// 7.3 Given two lines on the Cartesian, determine if they would intersect.
#include <cstdio>
using namespace std;

int main()
{
	// a * x + b * y + c = 0;
	// d * x + e * y + f = 0;
	int a, b, c, d, e, f;
	bool suc;
	
	while (scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f) == 6) {
		if ((a == 0 && b == 0) || (d == 0 && e == 0)) {
			// invalid line
			suc = false;
		} else if (a * e == b * d) {
			if (a * f == c *d) {
				// coincident
				suc = true;
			} else {
				// parallel
				suc = false;
			}
		} else {
			// intersect
			suc = true;
		}
		if (suc) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	}
	
	return 0;
}