// 17.14 Given a dictionary of words, and a long string. You may find a way to cut the string into words, where some of them may or may not be in the dictionary.
// Dynamic programming is a good thing, but trades space in for time.
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

int main()
{
	string data;
	unordered_set<string> dict;
	vector<vector<bool> > contains;
	vector<int> dp;
	int i, j;
	string s;
	int n;
	int tmp;
	
	while (cin >> data && data != "") {
		cin >> n;
		for (i = 0; i < n; ++i) {
			cin >> s;
			dict.insert(s);
		}
		n = (int)data.length();
		
		contains.resize(n);
		for (i = 0; i < n; ++i) {
			contains[i].resize(n);
		}
		for (i = 0; i < n; ++i) {
			s = "";
			for (j = i; j < n; ++j) {
				s.push_back(data[j]);
				contains[i][j] = (dict.find(s) != dict.end());
			}
		}
		
		dp.resize(n);
		for (i = 0; i < n; ++i) {
			dp[i] = contains[0][i] ? 0 : i + 1;
			for (j = 0; j < i; ++j) {
				tmp = dp[j] + (contains[j + 1][i] ? 0 : i - j);
				dp[i] = dp[i] < tmp ? dp[i] : tmp;
			}
		}
		
		printf("%d\n", dp[n - 1]);
		
		for (i = 0; i < n; ++i) {
			contains[i].clear();
		}
		contains.clear();
		dp.clear();
		dict.clear();
	}
	
	return 0;
}