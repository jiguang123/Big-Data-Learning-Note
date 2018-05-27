// 11.2 Sort an array of strings such that anagrams stay next to each other.
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string ta, tb;
int counting[256];

void countingSort(string &s)
{
	int i, j;

	for (i = 0; i < 256; ++i) {
		counting[i] = 0;
	}
	for (i = 0; i < (int)s.length(); ++i) {
		++counting[s[i]];
	}
	s.clear();

	for (i = 0; i < 256; ++i) {
		for (j = 0; j < counting[i]; ++j) {
			s.push_back(i);
		}
	}
}

bool anagramComparator(const string &a, const string &b)
{
	ta = a;
	tb = b;
	sort(ta.begin(), ta.end());
	sort(tb.begin(), tb.end());

	return ta < tb;
}

int main()
{
	vector<string> v;
	int i;
	int n;

	while (cin >> n && n > 0) {
		v.resize(n);
		for (i = 0; i < n; ++i) {
			cin >> v[i];
		}
		sort(v.begin(), v.end(), anagramComparator);
		for (i = 0; i < n; ++i) {
			if (i > 0) {
				cout << ' ';
			}
			cout << v[i];
		}
		cout << endl;
	}
	
	return 0;
}