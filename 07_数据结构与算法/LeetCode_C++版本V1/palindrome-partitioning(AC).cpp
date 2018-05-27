// 1CE, 2RE, 1AC, beware of subscript overflow.
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<string> > partition(string s) {
		int i;
		
		len = (int)s.length();
		for (i = 0; i < (int)result.size(); ++i) {
			result[i].clear();
		}
		result.clear();

		for (i = 0; i < 256; ++i) {
			pos.push_back(vector<int>());
		}
		// record the position of each characters
		for (i = 0; i < len; ++i) {
			pos[s[i]].push_back(i);
		}
		dfs(s, 0);
		
		// clean up
		vl.clear();
		vr.clear();
		for (i = 0; i < 256; ++i) {
			pos[i].clear();
		}
		pos.clear();
		
		return result;
    }
private:
	vector<int> vl, vr;
	int len;
	vector<vector<string> > result;
	vector<string> single_result;
	vector<vector<int> > pos;
	
	void dfs(const string &s, int idx) {
		int i, j;
		if (idx == len) {
			for (i = 0; i < (int)vl.size(); ++i) {
				single_result.push_back(s.substr(vl[i], vr[i] - vl[i] + 1));
			}
			result.push_back(vector<string>(single_result));
			single_result.clear();
			return;
		}
		
		int ll, rr;
		ll = idx;
		for (i = (int)pos[s[idx]].size() - 1; i >= 0 && pos[s[idx]][i] >= idx; --i) {
			rr = pos[s[idx]][i];
			for (j = ll; j < ll + rr - j; ++j) {
				if (s[j] != s[ll + rr - j]) {
					break;
				}
			}
			if (j >= ll + rr - j) {
				// a palindromic substring is found
				vl.push_back(ll);
				vr.push_back(rr);
				dfs(s, rr + 1);
				vl.pop_back();
				vr.pop_back();
			}
		}
	}
};