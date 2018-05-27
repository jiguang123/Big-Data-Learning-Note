// 5.4 Show what the code "n & (n - 1) == 0" means.
#include <cstdio>
using namespace std;

int main()
{
	unsigned int n;
	
	while (scanf("%u", &n) == 1) {
		if ((n & n - 1) == 0) {
			printf("%u is a power of 2.\n", n);
		} else {
			printf("%u is not a power of 2.\n", n);
		}
	}
	
	return 0;
}