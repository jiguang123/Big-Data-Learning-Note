// 17.3 Count how many zeros are there in n!?
// Count the number of 5s in n!.
#include <cstdio>
using namespace std;

int countZero(int n)
{
	int res = 0;
	
	while (n > 0) {
		res += n / 5;
		n /= 5;
	}
	
	return res;
}

int main()
{
	int n;
	
	
	while (scanf("%d", &n) == 1) {
		printf("%d\n", countZero(n));
	}
	
	return 0;
}