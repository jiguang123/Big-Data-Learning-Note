// 17.7 Read an integer in English.
#include <map>
#include <string>
using namespace std;

map<int, string> m;

void init()
{
	m[0] = "zero";
	m[1] = "one";
	m[2] = "two";
	m[3] = "three";
	m[4] = "four";
	m[5] = "five";
	m[6] = "six";
	m[7] = "seven";
	m[8] = "eight";
	m[9] = "nine";
	m[10] = "ten";
	m[11] = "eleven";
	m[12] = "twelve";
	m[13] = "thirteen";
	m[14] = "fourteen";
	m[15] = "fifteen";
	m[16] = "sixteen";
	m[17] = "seventeen";
	m[18] = "eighteen";
	m[19] = "nineteen";
	m[20] = "twenty";
	m[30] = "thirty";
	m[40] = "forty";
	m[50] = "fifty";
	m[60] = "sixty";
	m[70] = "seventy";
	m[80] = "eighty";
	m[90] = "ninety";
	int i, j;
	for (i = 2; i <= 9; ++i) {
		for (j = 1; j <= 9; ++j) {
			m[i * 10 + j] = m[i * 10] + "-" + m[j];
		}
	}
}

void readNumber(int n)
{
	if (n == 0) {
		return;
	}
	// here n is limited between [0, 999];
	int a, b, c;
	
	a = n / 100;
	b = n % 100 / 10;
	c = n % 10 / 1;
	
	if (a > 0) {
		printf("%s hundred ", m[a].c_str());
		if (b != 0 || c != 0) {
			printf("and ");
		}
	}
	if (b * 10 + c > 0) {
		printf("%s ", m[b * 10 + c].c_str());
	}
}

int main()
{
	init();
	int n, n0;
	
	while (scanf("%d", &n) == 1) {
		if (n == 0) {
			printf("zero \n");
			continue;
		}
		if (n < 0) {
			printf("minus ");
			n = -n;
		}
		n0 = n;
		if (n >= 1000000000) {
			readNumber(n / 1000000000);
			printf("billion ");
			n = n % 1000000000;
		}
		if (n >= 1000000) {
			readNumber(n / 1000000);
			n = n % 1000000;
			printf("million ");
		}
		if (n >= 1000) {
			readNumber(n / 1000);
			n = n % 1000;
			printf("thousand ");
		}
		if (n0 >= 1000 && n / 100 == 0) {
			printf("and ");
		}
		readNumber(n);
		putchar('\n');
	}
	
	return 0;
}