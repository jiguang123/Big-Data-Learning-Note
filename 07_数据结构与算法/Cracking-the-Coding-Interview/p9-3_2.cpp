// 9.3 Given a sorted array, find a position where A[i] = i, if one exists. The array may have duplicates.
#include <cstdio>
#include <vector>
using namespace std;

int findMagicIndex(vector<int> &v, int start, int end)
{
	if (start > end || start > (int)v.size() - 1 || end < 0) {
		return -1;
	}
	int mid = (start + end) / 2;
	if (v[mid] == mid) {
		return mid;
	}
	
	int res = findMagicIndex(v, start, (mid - 1 < v[mid] ? mid - 1 : v[mid]));
	if (res >= 0) {
		return res;
	}
	res = findMagicIndex(v, (mid + 1 > v[mid] ? mid + 1 : v[mid]), end);
	return res;
}

int main()
{
	vector<int> v;
	int n;
	int i;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		v.resize(n);
		for (i = 0; i < n; ++i) {
			scanf("%d", &v[i]);
		}
		printf("%d\n", findMagicIndex(v, 0, n - 1));
		
		v.clear();
	}
	
	return 0;
}