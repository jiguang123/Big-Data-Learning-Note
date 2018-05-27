// 5.5 Determine the number of bits required to convert integer A to B.
#include <cstdio>
using namespace std;

int numberOfOnes(unsigned int n)
{
	int res = 0;
	
	while (n != 0) {
		n = n & (n - 1);
		++res;
	}
	
	return res;
}

int main()
{
	unsigned int a, b;
	
	while (scanf("%u%u", &a, &b) == 2) {
		printf("%d\n", numberOfOnes(a ^ b));
	}
	
	return 0;
}