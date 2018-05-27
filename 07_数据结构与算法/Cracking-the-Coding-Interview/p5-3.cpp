// 5.3 Find the next largest number that have same number of '1's with the given number.
#include <cstdio>
using namespace std;

unsigned int findNext(unsigned int n)
{
	int n_zero;
	int n_one;
	
	n_zero = 0;
	while (n_zero < 32 && (n & (1 << n_zero)) == 0) {
		++n_zero;
	}
	if (n_zero == 32) {
		// all 0
		return n;
	}
	
	n_one = n_zero;
	while (n_one < 32 && (n & (1 << n_one)) != 0) {
		++n_one;
	}
	if (n_one  == 32) {
		// no larger number is possible
		return n;
	}
	
	n = n >> n_one << n_one;
	n |= (1 << n_one);
	for (int i = 0; i < n_one - n_zero - 1; ++i) {
		n |= (1 << i);
	}
	
	return n;
}

int main()
{
	unsigned int n;
	
	while (scanf("%u", &n) == 1) {
		printf("%u\n", findNext(n));
	}
	
	return 0;
}