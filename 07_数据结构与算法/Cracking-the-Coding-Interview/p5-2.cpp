// 5.2 Given a double, print its binary representation if can be done in 32 characters.
#include <cstdio>
using namespace std;

void printBinary(unsigned long long num)
{
	unsigned long long bit = 1ull << 63;
	do {
		putchar('0' + !!(num & bit));
		if ((bit == 1ull << 63) || (bit == 1ull << 52)) {
			putchar(' ');
		}
		bit >>= 1;
	} while (bit);
}

union un {
	unsigned long long ull;
	double d;
};

int main()
{
	double d;
	int exp;
	int ll, rr;
	int i;
	unsigned long long sig;
	un u;
	
	while (scanf("%lf", &d) == 1) {
		u.d = d;
		printBinary(u.ull);
		putchar('\n');
		// 1.5 is represented as 1 + 1 * 2^-1, so the '1' must be added to the significant.
		sig = (u.ull - (u.ull >> 52 << 52)) | (1ull << 52);
		// exponent has an offset of 127
		exp = 1022 - (int)(u.ull >> 52 & ~(1ull << 11));

		ll = 52;
		rr = 0;
		while ((sig & (1ull << rr)) == 0) {
			++rr;
		}
		
		if (ll - rr + 1 + exp <= 30) {
			// '0.' will take 2 characters, so 30 characters available
			printf("0.");
			for (i = 0; i < exp; ++i) {
				putchar('0');
			}
			for (i = ll;i >= rr; --i) {
				putchar('0' + !!(sig & (1ull << i)));
			}
			putchar('\n');
		} else {
			printf("ERROR\n");
		}
	}
	
	return 0;
}