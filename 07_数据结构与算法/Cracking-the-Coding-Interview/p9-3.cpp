// 9.3 Given a unique sorted array, find a position where A[i] = i, if one exists.
#include <cstdio>
#include <vector>
using namespace std;

int main()
{
	vector<int> v;
	int n;
	int i;
	int ll, rr, mm;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		v.resize(n);
		for (i = 0; i < n; ++i) {
			scanf("%d", &v[i]);
		}
		if (v[0] > 0 || v[n - 1] < n - 1) {
			mm = -1;
		} else {
			ll = 0;
			rr = n - 1;
			while (ll <= rr) {
				mm = (ll + rr) / 2;
				if (v[mm] < mm) {
					ll = mm + 1;
				} else if (v[mm] > mm) {
					rr = mm - 1;
				} else {
					break;
				}
			}
			if (ll > rr) {
				mm = -1;
			}
		}
		printf("%d\n", mm);
		
		v.clear();
	}
	
	return 0;
}