// 9.9 Eight-Queen Problem, need I say more?
#include <cstdio>
#include <vector>
using namespace std;

class Solution
{
public:
	void eigthQueens(int n, vector<vector<int> > &result) {
		if (n < 1) {
			return;
		}
		
		vector<int> v;
		dfs(0, n, v, result);
		v.clear();
	}
private:
	void dfs(int idx, int n, vector<int> &v, vector<vector<int> > &result) {
		if (idx == n) {
			result.push_back(v);
			return;
		}

		int i, j;
		for (i = 0; i < n; ++i) {
			for (j = 0; j < idx; ++j) {
				if (v[j] == i || myabs(idx - j) == myabs(i - v[j])) {
					// conflict
					break;
				}
			}
			if (j == idx) {
				v.push_back(i);
				dfs(idx + 1, n, v, result);
				v.pop_back();
			}
		}
	}
	
	int myabs(int n) {	
		return (n >= 0 ? n : -n);
	}
};

int main()
{
	vector<vector<int> > result;
	Solution sol;
	int n;
	int i, j, k;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		sol.eigthQueens(n, result);
		for (k = 0; k < (int)result.size(); ++k) {
			for (i = 0; i < n; ++i) {
				for (j = 0; j < result[k][i]; ++j) {
					putchar('0');
				}
				putchar('1');
				for (j = result[k][i] + 1; j < n; ++j) {
					putchar('0');
				}
				putchar('\n');
			}
			putchar('\n');
		}
		printf("%d\n", (int)result.size());
		for (i = 0; i < (int)result.size(); ++i) {
			result[i].clear();
		}
		result.clear();
	}
	
	return 0;
}