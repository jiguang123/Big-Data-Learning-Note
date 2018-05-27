// 17.8 Find the consecutive subarray with maximum sum in an array.
// O(n) online algorithm.
#include <cstdio>
#include <vector>
using namespace std;

int maximumSum(vector<int> &v)
{
	int n = (int)v.size();
	
	if (n == 0) {
		return 0;
	}
	
	int val = v[0];
	int i;
	
	for (i = 1; i < n; ++i) {
		val = val > v[i] ? val : v[i];
	}
	
	if (val <= 0) {
		return val;
	}
	
	int res;
	res = val = 0;
	for (i = 0; i < n; ++i) {
		val += v[i];
		if (val > res) {
			res = val;
		}
		if (val < 0) {
			val = 0;
		}
	}
	
	return res;
}

int main()
{
	vector<int> v;
	int n, i;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		v.resize(n);
		for (i = 0; i < n; ++i) {
			scanf("%d", &v[i]);
		}
		printf("%d\n", maximumSum(v));
		v.clear();
	}
	
	return 0;
}