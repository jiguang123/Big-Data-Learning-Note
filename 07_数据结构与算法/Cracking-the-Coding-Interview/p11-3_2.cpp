// 11.3 Given a sorted array rotated by a few positions, find out if a value exists in the array.
// Suppose the array may contain duplicates, what's it gonna be then?
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
	int i;
	
	ll = 0;
	rr = n - 1;
	while (rr - ll > 1 && v[ll] == v[rr]) {
		mm = (ll + rr) / 2;
		if (v[mm] > v[ll]) {
			ll = mm;
			break;
		} else if (v[mm] < v[ll]) {
			rr = mm;
			break;
		} else {
			for (i = ll; i < mm - 1; ++i) {
				if (v[i] != v[i + 1]) {
					break;
				}
			}
			if (i < mm - 1) {
				rr = mm;
				break;
			}
			for (i = mm; i < rr - 1; ++i) {
				if (v[i] != v[i + 1]) {
					break;
				}
			}
			if (i < rr - 1) {
				break;
			}
			
			// if all elements are the same, it ends here
			return (v[0] == key) ? 0 : -1;
		}
	}
	
	if (v[ll] < v[rr]) {
		offset = 0;
	} else {
		// here it is guaranteed v[ll] != v[rr]
		while (rr - ll > 1) {
			mm = (ll + rr) / 2;
			if (v[mm] >= v[ll]) {
				ll = mm;
			} else {
				rr = mm;
			}
		}
		offset = rr;
	}
	
	// the binary search part remains the same, difference lies in how we find the 'offset'.
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