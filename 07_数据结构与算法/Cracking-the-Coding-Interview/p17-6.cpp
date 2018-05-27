// 17.6 Given an array, if you sort a subarray of it, the total array will become sorted. Find the length of the shortest of all such subarrays.
#include <cstdio>
#include <vector>
using namespace std;

void findUnsortedSequence(vector<int> &v, int &left_index, int &right_index)
{
	int n = v.size();
	
	left_index = right_index = -1;
	if (n < 2) {
		return;
	}
	int val;
	int i;
	
	val = v[0];
	for (i = 1; i <= n - 1; ++i) {
		val = v[i] > val ? v[i] : val;
		if (v[i] < val) {
			right_index = i;
		}
	}
	
	val = v[n - 1];
	for (i = n - 2; i >= 0; --i) {
		val = v[i] < val ? v[i] : val;
		if (v[i] > val) {
			left_index = i;
		}
	}
}

int main()
{
	vector<int> v;
	int i;
	int n;
	int left_index, right_index;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		v.resize(n);
		for (i = 0; i < n; ++i) {
			scanf("%d", &v[i]);
		}
		findUnsortedSequence(v, left_index, right_index);
		printf("(%d, %d)\n", left_index, right_index);
		v.clear();
	}
	
	return 0;
}