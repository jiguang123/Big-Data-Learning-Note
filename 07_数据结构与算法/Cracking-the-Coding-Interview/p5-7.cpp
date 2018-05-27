// 5.7 Find the missing integer from 0 to n, you may only access one bit at a time.
#include <cstdio>
#include <vector>
using namespace std;

inline int getBit(vector<int> &v, int i, int j)
{
	return !!(v[i] & (1 << j));
}

int main()
{
	int n;
	int mis;
	int i, j;
	long long int sum;
	long long int tot_sum;
	vector<int> v;
	
	while (scanf("%d%d", &n, &mis) == 2) {
		tot_sum = (1ll + n) * n / 2;
		sum = 0;
		for (i = 0; i <= n; ++i) {
			if (i == mis) {
				continue;
			}
			v.push_back(i);
		}
		
		sum = 0;
		for (i = 0; i < n; ++i) {
			for (j = 0; j < 32; ++j) {
				sum += (getBit(v, i, j) << j);
			}
		}
		printf("%lld\n", tot_sum - sum);
		
		v.clear();
	}
	
	return 0;
}