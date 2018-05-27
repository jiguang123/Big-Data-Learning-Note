// 17.12 Given an array of integers and target value, find all pairs in the array that sum up to the target.
// O(n * log(n) + n) solution.
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

int main()
{
	vector<int> v;
	int n, i;
	int ll, rr;
	int target;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		scanf("%d", &target);
		
		v.resize(n);
		for (i = 0; i < n; ++i) {
			scanf("%d", &v[i]);
		}
		sort(v.begin(), v.end());
		ll = 0;
		rr = n - 1;
		
		int sum;
		while (ll < rr) {
			sum = v[ll] + v[rr];
			if (sum < target) {
				while (ll + 1 < rr && v[ll] == v[ll + 1]) {
					++ll;
				}
				++ll;
			} else if (sum > target) {
				while (rr - 1 > ll && v[rr] == v[rr - 1]) {
					--rr;
				}
				--rr;
			} else {
				printf("(%d, %d)\n", v[ll], v[rr]);
				while (ll + 1 < rr && v[ll] == v[ll + 1]) {
					++ll;
				}
				++ll;
			}
		}
		
		v.clear();
	}
	
	return 0;
}