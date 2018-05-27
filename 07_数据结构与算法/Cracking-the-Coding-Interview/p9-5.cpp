// 9.5 Print all permutations of a string.
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

void countingSort(char s[], int n)
{
	static int c[256];
	
	if (s == nullptr || n < 2) {
		return;
	}
	
	int i, j;
	
	memset(c, 0, 256 * sizeof(int));
	for (i = 0; i < n; ++i) {
		++c[s[i]];
	}
	
	n = 0;
	for (i = 0; i < 256; ++i) {
		for (j = 0; j < c[i]; ++j) {
			s[n++] = i;
		}
	}
	s[n] = 0;
}

bool myNextPermutation(char s[], int n)
{
	if (s == nullptr) {
		return false;
	}
	
	int i;
	int ll, rr, mm;
	char ch;
	
	for (i = n - 2; i >= 0; --i) {
		if (s[i] < s[i + 1]) {
			ll = i + 1;
			rr = n - 1;
			break;
		}
	}
	
	if (i < 0) {
		return false;
	}
	
	if (s[rr] > s[i]) {
		ch = s[rr];
		s[rr] = s[i];
		s[i] = ch;
	} else {
		while (rr - ll > 1) {
			mm = (ll + rr) / 2;
			if (s[mm] > s[i]) {
				ll = mm;
			} else {
				rr = mm;
			}
		}
		ch = s[ll];
		s[ll] = s[i];
		s[i] = ch;
	}
	
	ll = i + 1;
	rr = n - 1;
	for (i = ll; i < ll + rr - i; ++i) {
		ch = s[i];
		s[i] = s[ll + rr - i];
		s[ll + rr - i] = ch;
	}
	return true;
}

int main()
{
	char s[100];
	int len;
	
	while (scanf("%s", s) == 1 && (len = strlen(s)) > 0) {
		countingSort(s, len);
		do {
			puts(s);
		} while (myNextPermutation(s, len));
	}
	
	return 0;
}