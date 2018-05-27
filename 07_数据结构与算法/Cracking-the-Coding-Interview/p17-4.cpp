// 17.4 Find the maximum of two numbers without using comparison operator or if-else statement.
// Use bit operation instead. But this solution applies to integer only.
#include <cstdio>
using namespace std;

int mymax(int x, int y)
{
	static const unsigned mask = 0x80000000;
	return (x & mask) ^ (y & mask) ? ((x & mask) ? y : x) : ((x - y & mask) ? y : x);
}

int main()
{
	int x, y;
	
	while (scanf("%d%d", &x, &y) == 2) {
		printf("%d\n", mymax(x, y));
	}
	
	return 0;
}