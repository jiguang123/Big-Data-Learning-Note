// 9.8 Given unlimited quarters(25 cents), dimes(10 cents), nickels(5 cents) and pennies(1 cent), how many ways are there to represent n cents.
#include <cstdio>
#include <vector>
using namespace std;

// f(n, 1) = 1;
// f(n, 1, 5) = sigma(i in [0, n / 5]){f(n - i * 5, 1)};
// f(n, 1, 5, 10) = sigma(i in [0, n / 10]){f(n - i * 10, 1, 5)}
// f(n, 1, 5, 10, 25) = sigma(i in [0, n / 25]){f(n - i * 25, 1, 5, 10)}
int main()
{
	int n;
	vector<vector<long long int> > v;
	const int MAXN = 1000000;
	const int c[4] = {1, 5, 10, 25};
	
	int i, j;
	v.resize(2);
	for (i = 0; i < 2; ++i) {
		v[i].resize(MAXN);
	}
	int flag = 1;
	int nflag = !flag;
	for (i = 0; i < MAXN; ++i) {
		v[0][i] = 1;
	}
	
	for (i = 1; i < 4; ++i) {
		for (j = 0; j < c[i]; ++j) {
			v[flag][j] = v[nflag][j];
		}
		for (j = c[i]; j < MAXN; ++j) {
			v[flag][j] = v[nflag][j] + v[flag][j - c[i]];
		}
		flag = !flag;
		nflag = !nflag;
	}
	flag = !flag;
	nflag = !nflag;
	
	while (scanf("%d", &n) == 1 && n >= 0 && n < MAXN) {
		printf("%lld\n", v[flag][n]);
	}
	for (i = 0; i < 2; ++i) {
		v[i].clear();
	}
	v.clear();
	
	return 0;
}