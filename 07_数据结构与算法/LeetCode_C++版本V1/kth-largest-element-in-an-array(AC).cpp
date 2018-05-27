// 1TLE, 1WA, 1AC, being bug-free is not easy.
class Solution {
public:
	int findKthLargest(vector<int>& nums, int k) {
		int n = nums.size();
		return quickSelect(nums, 0, n - 1, n - k);
	}
private:
	int quickSelect(vector<int> &a, int ll, int rr, int k) {
		if (ll == rr) {
			return a[ll];
		}
		
		int i, j;
		int piv = a[ll];
		
		i = ll + 1;
		j = rr;
		while (true) {
			while (i <= j && a[i] < piv) {
				++i;
			}
			while (i <= j && a[j] > piv) {
				--j;
			}
			if (i > j) {
				break;
			}
			swap(a[i++], a[j--]);
		}
		swap(a[j], a[ll]);
		if (k < j) {
			return quickSelect(a, ll, j - 1, k);
		} else if (k > j) {
			return quickSelect(a, j + 1, rr, k);
		} else {
			return a[k];
		}
	}
};