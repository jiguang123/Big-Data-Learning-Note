// 9.4 Return all subsets of a set
#include <cstdio>
#include <vector>
using namespace std;

void getSubsets(const vector<int> &v, int idx, vector<int> &buffer, vector<vector<int> > &res)
{
	if (idx == (int)v.size()) {
		res.push_back(buffer);
	} else {
		getSubsets(v, idx + 1, buffer, res);
		buffer.push_back(v[idx]);
		getSubsets(v, idx + 1, buffer, res);
		buffer.pop_back();
	}
}

int main()
{
	int i, j;
	vector<vector<int> > res;
	vector<int> v;
	vector<int> buffer;
	int n;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		v.resize(n);
		for (i = 0; i < n; ++i) {
			scanf("%d", &v[i]);
		}
		
		getSubsets(v, 0, buffer, res);
		
		for (i = 0; i < (int)res.size(); ++i) {
			printf("[");
			for (j = 0; j < (int)res[i].size(); ++j) {
				if (j == 0) {
					printf("%d", res[i][j]);
				} else {
					printf(" %d", res[i][j]);
				}
			}
			printf("]\n");
			res[i].clear();
		}
		res.clear();
		buffer.clear();
		v.clear();
	}
	
	return 0;
}