//#define ZZ
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool comparator(const string &s1, const string &s2)
{
	string s12, s21;

	s12 = s1 + s2;
	s21 = s2 + s1;

	bool res = s12 < s21;
	s12.clear();
	s21.clear();

	return res;
}

class Solution {
public:
    string largestNumber(vector<int> &num) {
		char s[100];
		vector<string>vs;

		int n, i;

		n = (int)num.size();
		for (i = 0; i < n; ++i) {
			sprintf(s, "%d", num[i]);
			vs.push_back(string(s));
		}

		sort(vs.begin(), vs.end(), comparator);
		string res = "";

		for (i = n - 1; i >= 0; --i) {
			res += vs[i];
		}
		vs.clear();

		i = 0;
		n = (int)res.length();
		while (i < n - 1 && res[i] == '0') {
			++i;
		}
		res = res.substr(i, n - i);

		return res;
    }
};

#ifdef ZZ
int main()
{
	vector<int> num;
	int n;
	int i;
	Solution sol;

	while (cin >> n) {
		num.resize(n);
		for (i = 0; i < n; ++i) {
			cin >> num[i];
		}
		cout << sol.largestNumber(num) << endl;
		num.clear();
	}

	return 0;
}
#endif