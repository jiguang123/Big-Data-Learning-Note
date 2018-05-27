// 9.6 Print all valid parentheses sequences of n ()s.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void DFS(int idx, int n, string s, vector<vector<string> > &result)
{
	if (idx == n) {
		result[n].push_back(s);
		return;
	} else {
		int i, j;
		for (i = 1; i <= n - idx; ++i) {
			for (j = 0; j < (int)result[i - 1].size(); ++j) {
				DFS(idx + i, n, s + '(' + result[i - 1][j] + ')', result);
			}
		}
	}
}

int main()
{
	vector<vector<string> > result;
	int n;
	int i;
	
	result.resize(1);
	result[0].push_back("");
	
	while (cin >> n && n > 0) {
		if (n >= (int)result.size()) {
			for (i = (int)result.size(); i <= n; ++i) {
				result.push_back(vector<string>());
				DFS(0, i, "", result);
			}
		}
		for (i = 0; i < (int)result[n].size(); ++i) {
			cout << result[n][i] << endl;
		}
	}
	
	return 0;
}