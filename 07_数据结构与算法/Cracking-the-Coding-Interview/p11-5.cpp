// 11.5 Given an array of strings interspersed with empty string ""s. Find out if a target string exists in the string.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	int i, j, n;
	int ns;
	string s;
	vector<string> v;
	int ll, rr, mm;
	
	while (cin >> n && n > 0) {
		cin >> ns;
		for (i = 0; i < ns; ++i) {
			v.push_back("");
		}
		for (i = 0; i < n; ++i) {
			cin >> s;
			v.push_back(s);
			cin >> ns;
			for (j = 0; j < ns; ++j) {
				v.push_back("");
			}
		}
		cin >> s;
		
		ll = 0;
		while (v[ll] == "") {
			++ll;
		}
		rr = (int)v.size() - 1;
		while (v[rr] == "") {
			--rr;
		}
		while (ll <= rr) {
			mm = (ll + rr) / 2;
			while (v[mm] == "") {
				// go left or right, either is OK.
				--mm;
			}
			if (s > v[mm]) {
				ll = mm + 1;
				while (ll <= rr && v[ll] == "") {
					++ll;
				}
			} else if (s < v[mm]) {
				rr = mm - 1;
				while (rr >= ll && v[rr] == "") {
					--rr;
				}
			} else {
				break;
			}
		}
		printf("%d\n", (ll <= rr ? mm : -1));
		
		v.clear();
	}
	
	return 0;
}