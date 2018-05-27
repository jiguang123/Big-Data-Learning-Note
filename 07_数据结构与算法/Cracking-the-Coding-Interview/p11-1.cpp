// 11.1 Given two sorted array A and B, suppose A is large enough to hold them both. Merge B into A.
#include <algorithm>
#include <cstdio>
using namespace std;

void mergeBIntoA(int a[], int b[], int na, int nb)
{
	if (na <= 0 || nb <= 0) {
		// invalid parameter
		return;
	}
	
	int *pmin, *pmax;
	pmin = min(a, b);
	pmax = max(a + na + nb, b + nb);
	if (pmax - pmin < na + nb + nb) {
		// the memories overlap
		return;
	}
	
	int i, j, k;
	
	i = na;
	j = nb;
	k = na + nb;
	
	while (i > 0 && j > 0) {
		if (a[i - 1] > b[j - 1]) {
			a[--k] = a[--i];
		} else {
			a[--k] = b[--j];
		}
	}
	while (j > 0) {
		a[--k] = b[--j];
	}
}

int main()
{
	int *a, *b;
	int na, nb;
	int i;
	
	while (scanf("%d%d", &na, &nb) ==  2 && (na > 0 && nb > 0)) {
		a = new int[na + nb];
		b = new int[nb];
		for (i = 0; i < na; ++i) {
			scanf("%d", &a[i]);
		}
		for (i = 0; i < nb; ++i) {
			scanf("%d", &b[i]);
		}
		mergeBIntoA(a, b, na, nb);
		for (i = 0; i < na + nb; ++i) {
			printf((i == 0 ? "%d" : " %d"), a[i]);
		}
		putchar('\n');
		
		delete[] a;
		delete[] b;
		a = nullptr;
		b = nullptr;
	}
	
	return 0;
}