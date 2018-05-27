// 6.6 Given n lights, every time you toggle the switches of k-multiples. k goes from 1 to n.
// Assume they're all off at first, how many of them are on at last.
#include <cstdio>
using namespace std;

// My solution:
//	For a number m between 1~n, the key is total number of divisors of m, defined as num_div(m).
//	The light m is toggled for num_div(m) times. If it is odd, light is on. Even and light is off.
//	Only perfect square can be factorized, where every prime factor has even exponents.
//	That is, m = p[0]^e[0] * p[1]^e[1] * ... * p[whatever]^e[whatever]
//	num_div(m) = (e[0] + 1) * (e[1] + 1) * ... * (e[whatever] + 1)
//	If num_div(m) is to be odd, every multiplier has to be odd, every e[i] has to be even.
//	Thus m has to be a perfect square, if light m is on at last.
int main()
{
	int n;
	int i;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 1; i <= n / i; ++i) {
			printf("%d ", i * i);
		}
		printf("\n");
		printf("%d light(s) is(are) on.\n", i - 1);
	}

	return 0;
}