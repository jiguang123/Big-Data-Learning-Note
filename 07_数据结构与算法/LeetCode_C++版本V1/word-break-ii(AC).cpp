// 3CE, 2TLE, 1WA, 1AC, DFS from right to left will do, while from left to right it wouldn't.
class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string> &dict) {
		result.clear();
		n = (int)s.length();
		if (n == 0 || dict.empty()) {
			return result;
		}
		
		dp.resize(n);
		int i, j;
		for (i = 0; i < n; ++i) {
			dp[i].resize(n - i);
		}
		
		string str;
		for (i = 0; i < n; ++i) {
			for (j = i; j < n; ++j) {
				str = s.substr(i, j - i + 1);
				if (dict.find(str) != dict.end()) {
					dp[i][j - i] = 1;
				} else {
					dp[i][j - i] = 0;
				}
			}
		}
		
		words.clear();
		dfs(s, n - 1);
		for (i = 0; i < n; ++i) {
			dp[i].clear();
		}
		dp.clear();
		
		return result;
    }
private:
	int n;
	vector<string> result;
	vector<string> words;
	vector<vector<int> > dp;
	
	void dfs(const string &s, int idx) {
		if (idx == -1) {
			getResultString();
		} else {
			int i;
			for (i = 0; i <= idx; ++i) {
				if (dp[i][idx - i]) {
					words.push_back(s.substr(i, idx - i + 1));
					dfs(s, i - 1);
					words.pop_back();
				}
			}
		}
	}
	
	void getResultString() {
		if (words.empty()) {
			return;
		}
		string str = words[(int)words.size() - 1];
		int i;
		for (i = (int)words.size() - 2; i >= 0; --i) {
			str += (" " + words[i]);
		}
		result.push_back(str);
	}
};