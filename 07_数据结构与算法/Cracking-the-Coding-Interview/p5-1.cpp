// 5.1 Insert one number into the certain bit segment of another number.
#include <cstdio>
using namespace std;

void printBinary(unsigned num)
{
	unsigned bit = 1 << 31;
	
	do {
		putchar('0' + !!(num & bit));
		bit >>= 1;
	} while (bit);
}

unsigned insertBits(unsigned n, unsigned m, int ll, int rr)
{
	return (n >> (rr + 1) << (rr + 1)) + (m << ll) + (n - (n >> ll << ll));
}

int main()
{
	unsigned n, m;
	unsigned res;
	int low, high;
	
	while (scanf("%u%u", &n, &m) == 2) {
		scanf("%d%d", &low, &high);
		res = insertBits(n, m, low, high);
		printBinary(n);
		putchar('\n');
		printBinary(m);
		putchar('\n');
		printBinary(res);
		putchar('\n');
	}
	
	return 0;
}