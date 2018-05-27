// 2MLE, 1AC, save some space.
//#define ZZ
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
		vector<string> res;

		res.clear();
		int len = s.length();
		int i;

		if (len < 10) {
			return res;
		}

		int sum = 0;
		for (i = 0; i < 10; ++i) {
			sum = (sum << 2) + dg(s[i]);
		}
		++c[sum];

		for (i = 1; i + 10 <= len; ++i) {
			sum = ((sum << 2) & 1048575) + dg(s[i + 9]);
			++c[sum];
		}

		string ss;
		int j;

		ss.resize(10);
		unordered_map<int, int>::iterator it;
		for (it = c.begin(); it != c.end(); ++it) {
			if (it->second < 2) {
				continue;
			}
			sum = it->first;
			for (j = 9; j >= 0; --j) {
				ss[9 - j] = gd(sum >> 2 * j);
				sum &= ((1 << 2 * j) - 1);
			}
			res.push_back(ss);
		}
		c.clear();
		return res;
    }
private:
	unordered_map<int, int> c;

	int dg(char ch) {
		if (ch == 'A') {
			return 0;
		} else if (ch == 'C') {
			return 1;
		} else if (ch == 'G') {
			return 2;
		} else if (ch == 'T') {
			return 3;
		} else {
			return 0;
		}
	}

	char gd(int d)
	{
		if (d == 0) {
			return 'A';
		} else if (d == 1) {
			return 'C';
		} else if (d == 2) {
			return 'G';
		} else if (d == 3) {
			return 'T';
		} else {
			return 0;
		}
	}
};
#ifdef ZZ
int main()
{
	Solution sol;
	string s;
	vector<string> res;
	int i;

	while (cin >> s) {
		res = sol.findRepeatedDnaSequences(s);
		for (i = 0; i < res.size(); ++i) {
			cout << res[i] << endl;
		}
		res.clear();
	}

	return 0;
}
#endif