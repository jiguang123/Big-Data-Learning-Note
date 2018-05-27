// 18.6 Find the smallest one million number among one billion numbers.
// Suppose one billion numbers can fit in memory.
// I'll use quick selection algorithm to find them. This will return an unsorted result.
// Time complexity is O(n), but the constant factor may be massive. I don't quite like this algorithm.
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int CUT_OFF = 3;

int medianThree(vector<int> &v, int ll, int rr)
{
	int mm = (ll + rr) / 2;

	if (v[ll] > v[mm]) {
		swap(v[ll], v[mm]);
	}
	if (v[ll] > v[rr]) {
		swap(v[ll], v[rr]);
	}
	if (v[mm] > v[rr]) {
		swap(v[mm], v[rr]);
	}
	swap(v[mm], v[rr - 1]);
	return v[rr - 1];
}

void quickSelect(vector<int> &v, int ll, int rr, int k)
{
	// reference from "Data Structure and Algorithm Analysis in C" by Mark Allen Weiss.
	int pivot;
	int i, j;
	
	if (ll + CUT_OFF <=	rr) {
		pivot = medianThree(v, ll, rr);
		i = ll;
		j = rr - 1;
		
		while (true) {
			while (v[++i] < pivot);
			while (v[--j] > pivot);
			if (i > j) {
				break;
			}
			swap(v[i], v[j]);
		}
		swap(v[i], v[rr - 1]);
	
		if (k < i) {
			return quickSelect(v, ll, i - 1, k);
		} else if (k > i) {
			return quickSelect(v, i + 1, rr, k);
		}
	} else {
		for (i = ll; i <= rr; ++i) {
			for (j = i + 1; j <= rr; ++j) {
				if (v[i] > v[j]) {
					swap(v[i], v[j]);
				}
			}
		}
	}
}

int main()
{
	vector<int> v;
	vector<int> res;
	int n, k;
	int i;
	int k_small, count;
	
	while (cin >> n >> k && (n > 0 && k > 0)) {
		v.resize(n);
		for (i = 0; i < n; ++i) {
			cin >> v[i];
		}

		// find the kth smallest number
		// this will change the order of elements
		quickSelect(v, 0, n - 1, k - 1);
		k_small = v[k - 1];
		count = k;
		for (i = 0; i < n; ++i) {
			if (v[i] < k_small) {
				--count;
			}
		}
		for (i = 0; i < n; ++i) {
			if (v[i] < k_small) {
				res.push_back(v[i]);
			} else if (v[i] == k_small && count > 0) {
				res.push_back(v[i]);
				--count;
			}
		}
		
		cout << '{';
		for (i = 0; i < k; ++i) {
			i ? (cout << ' '), 1 : 1;
			cout << res[i];
		}
		cout << '}' << endl;
		
		v.clear();
		res.clear();
	}
	
	return 0;
}