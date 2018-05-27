// 1AC, excellent!
// #define MY_MAIN
#include <algorithm>
#include <cstdio>
#include <map>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int> > fourSum(vector<int> &num, int target) {
		int n;
		int a, b, c, d;
		int s;
		vector<int> vtmp;
		char str[100];
		
		for (n = 0; n < (int)result.size(); ++n) {
			result[n].clear();
		}
		result.clear();
		signs.clear();
		vtmp.clear();

		// sort the array first
		sort(num.begin(), num.end());
		n = (int)num.size();
		for (a = 0; a < n; ++a) {
			for (d = a + 3; d < n; ++d) {
				if (num[a] + num[d - 2] + num[d - 1] + num[d] < target) {
					// too small
					continue;
				}
				if (num[a] + num[a + 1] + num[a + 2] + num[d] > target) {
					// too large
					continue;
				}
				
				b = a + 1;
				c = d - 1;
				s = target - num[a] - num[d];
				while (true) {
					if (b >= c) {
						// edge is crossed
						break;
					}
					if (num[b] + num[c] < s) {
						++b;
					} else if (num[b] + num[c] > s) {
						--c;
					} else {
						str[0] = 0;
						// create a digital sign to detect duplicates.
						sprintf(str, "%d%d%d%d", num[a], num[b], num[c], num[d]);
						string ss = string(str);
						if (signs.find(ss) == signs.end()) {
							signs[ss] = 1;
							vtmp.clear();
							vtmp.push_back(num[a]);
							vtmp.push_back(num[b]);
							vtmp.push_back(num[c]);
							vtmp.push_back(num[d]);
							result.push_back(vtmp);
						}
						++b;
						--c;
					}
				}
			}
		}
		
		return result;
    }
private:
	vector<vector<int> > result;
	map<string, int> signs;
};

#ifdef MY_MAIN
int main()
{
	int target;
	vector<int> num;
	int n;
	int tmp;
	Solution solution;
	vector<vector<int> > result;
	int i, j;
	
	while (scanf("%d%d", &n, &target) == 2) {
		num.clear();
		for (i = 0; i < n; ++i) {
			scanf("%d", &tmp);
			num.push_back(tmp);
		}
		result = solution.fourSum(num, target);
		printf("A solution set is:\n");
		for (i = 0; i < (int)result.size(); ++i) {
			printf("(%d", result[i][0]);
			for (j = 1; j < 4; ++j) {
				printf(", %d", result[i][j]);
			}
			printf(")\n");
		}
		printf("\n");
	}
	
	return 0;
}
#endif