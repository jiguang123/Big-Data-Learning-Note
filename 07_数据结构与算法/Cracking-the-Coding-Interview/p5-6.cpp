// 5.6 Swap odd and even bits in an integer.
#include <cstdio>
using namespace std;

unsigned int swapBits(unsigned int n)
{
	static const unsigned int mask[2] = {0x55555555, 0xaaaaaaaa};
	
	return ((n & mask[0]) << 1) + ((n & mask[1]) >> 1);
}

int main()
{
	unsigned int n;
	
	while (scanf("%u", &n) == 1) {
		printf("%u\n", swapBits(n));
	}
	
	return 0;
}