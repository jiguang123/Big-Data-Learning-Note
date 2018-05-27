// 11.3 Given a sorted array rotated by a few positions, find out if a value exists in the array.
// Suppose all elements in the array are unique.
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

int rotatedBinarySearch(vector<int> &v, int n, int key)
{
	int offset;
	
	if ((int)v.size() < n || n <= 0) {
		return -1;
	}
	
	int ll, rr, mm;

	if (v[0] < v[n - 1]) {
		offset = 0;
	} else {
		ll = 0;
		rr = n - 1;
		while (rr - ll > 1) {
			mm = (ll + rr) / 2;
			if (v[mm] > v[ll]) {
				ll = mm;
			} else {
				rr = mm;
			}
		}
		offset = rr;
	}
	
	ll = 0;
	rr = n - 1;
	while (ll <= rr) {
		mm = (ll + rr) / 2;
		if (key < v[(mm + offset) % n]) {
			rr = mm - 1;
		} else if (key > v[(mm + offset) % n]) {
			ll = mm + 1;
		} else {
			return (mm + offset) % n;
		}
	}
	return -1;
}

int main()
{
	int n;
	int i;
	vector<int> v;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		v.resize(n);
		for (i = 0; i < n; ++i) {
			scanf("%d", &v[i]);
		}
		scanf("%d", &i);
		printf("%d\n", rotatedBinarySearch(v, n, i));
	}
	
	return 0;
}