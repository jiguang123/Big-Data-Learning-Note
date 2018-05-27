// 1AC, good~
// #define MY_MAIN
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string getPermutation(int n, int k) {
		const int fac[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
		int i, j, tmp;
		int div;
		string result;
		
		--k;
		permutation.clear();
		for (i = 1; i <= n; ++i) {
			permutation.push_back(i);
		}
		
		for (i = n - 1; i >= 1; --i) {
			div = k / fac[i];
			tmp = permutation[n - 1 - i + div];
			for (j = 0; j < div; ++j) {
				permutation[n - 1 - i + div - j] = permutation[n - 1 - i + div - j - 1];
			}
			permutation[n - 1 - i] = tmp;
			k = k % fac[i];
		}
		
		result = "";
		for (i = 0; i < n; ++i) {
			sprintf(s, "%d", permutation[i]);
			result = result + string(s);
		}
		permutation.clear();
		
		return result;
    }
private:
	vector<int> permutation;
	char s[100];
};

#ifdef MY_MAIN
int main()
{
	Solution solution;
	int n, k;
	const int fac[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
	
	while (scanf("%d%d", &n, &k) == 2) {
		if (n < 1 || n > 9) {
			continue;
		}
		if (k < 1 || k > fac[n]) {
			continue;
		}
		printf("%s\n", solution.getPermutation(n, k).c_str());
	}
	
	return 0;
}
#endif