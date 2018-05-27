// 7.4 Implement the -*/ function with only the + operator.
// You cannot use bit operation, although you might want it for efficiency.
#include <cstdio>
using namespace std;

int negate(int n)
{
	int one = (n >= 0 ? -1 : 1);
	int res = 0;
	
	while (n != 0) {
		n += one;
		res += one;
	}
	
	return res;
}

int add(int x, int y)
{
	return x + y;
}

int subtract(int x, int y)
{
	return x + negate(y);
}

int multiply(int x, int y)
{
	int res = 0;
	int value = (x >= 0 ? y : negate(y));
	int one = (x >= 0 ? -1 : 1);
	
	while (x != 0) {
		res += value;
		x += one;
	}
	
	return res;
}

int divide(int x, int y)
{
	if (y == 0) {
		return 0;
	}
	if (x == 0) {
		return 0;
	}
	
	int res = 0;
	int one = 1;
	int negone = -1;
	int negy = negate(y);
	
	if (x > 0) {
		if (y > 0) {
			while (x >= y) {
				x += negy;
				res += one;
			}
		} else {
			while (x >= negy) {
				x += y;
				res += negone;
			}
		}
	} else {
		if (y > 0) {
			while (x <= negy) {
				x += y;
				res += negone;
			}
		} else {
			while (x <= y) {
				x += negy;
				res += one;
			}
		}
	}
	
	return res;
}

int main()
{
	char s[10];
	int a, b;
	int res;
	
	while (scanf("%d%s%d", &a, s, &b) == 3) {
		switch (s[0]) {
		case '+':
			res = add(a, b);
			break;
		case '-':
			res = subtract(a, b);
			break;
		case '*':
			res = multiply(a, b);
			break;
		case '/':
			res = divide(a, b);
			break;
		}
		printf("%d\n", res);
	}
	
	return 0;
}