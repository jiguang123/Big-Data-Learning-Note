// 18.7 Given a list of words, find out the longest word made of other words in the list.
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
	string longestBreakableWord(unordered_set<string> &dict) {
		unordered_set<string>::const_iterator usit;
		string res = "";
		
		for (usit = dict.begin(); usit != dict.end(); ++usit) {
			if (wordBreak(*usit, dict) && usit->length() > res.length()) {
				res = *usit;
			}
		}
		
		return res;
	}
private:
    bool wordBreak(string s, unordered_set<string> &dict) {
		int n;
		int i, j;
		string str;
		vector<int> dp;
		
		n = (int)s.length();
		if (n == 0 || dict.empty()) {
			return false;
		}
		dp.resize(n);
		for (i = 0; i < n; ++i) {
			str = s.substr(0, i + 1);
			if (dict.find(str) != dict.end()) {
				dp[i] = 1;
			} else {
				for (j = 0; j < i; ++j) {
					if (dp[j] && dict.find(s.substr(j + 1, i - j)) != dict.end()) {
						dp[i] = 1;
						break;
					}
				}
				if (j == i) {
					dp[i] = 0;
				}
			}
		}
		
		i = dp[n - 1];
		dp.clear();
		return i == 1;
    }
};

int main()
{
	unordered_set<string> dict;
	string s;
	Solution sol;
	int i, n;
	
	while (cin >> n && n > 0) {
		for (i = 0; i < n; ++i) {
			cin >> s;
			dict.insert(s);
		}
		
		cout << sol.longestBreakableWord(dict) << endl;
	}
	
	return 0;
}