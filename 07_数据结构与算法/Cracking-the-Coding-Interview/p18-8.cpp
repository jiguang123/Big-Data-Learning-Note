// 18.8 Given a list of words and a piece of text, find out how many times in total, all words appear in the text.
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
	int KMPMatch(const string &word, const string &pattern) {
		int index;
		int pos;
		int result;
		
		lw = word.length();
		lp = pattern.length();
		calculateNext(pattern);

		index = pos = 0;
		result = 0;
		while (index < lw) {
			if (pos == -1 || word[index] == pattern[pos]) {
				++index;
				++pos;
			} else {
				pos = next[pos];
			}
			
			if (pos == lp) {
				pos = 0;
				++result;
			}
		}
		
		return result;
	};
	
	~Solution() {
		next.clear();
	};
private:
	int lw;
	int lp;
	vector<int> next;
	
	void calculateNext(const string &pattern) {
		int i = 0;
		int j = -1;
		
		next.resize(lp + 1);
		next[0] = -1;
		while (i < lp) {
			if (j == -1 || pattern[i] == pattern[j]) {
				++i;
				++j;
				next[i] = j;
			} else {
				j = next[j];
			}
		}
	};
};

int main()
{
	string text;
	unordered_set<string> dict;
	Solution sol;
	int n, i;
	int sum;
	
	while (cin >> n && n > 0) {
		for (i = 0; i < n; ++i) {
			cin >> text;
			dict.insert(text);
		}
		cin >> text;
		
		sum = 0;
		unordered_set<string>::const_iterator usit;
		for (usit = dict.begin(); usit != dict.end(); ++usit) {
			sum += sol.KMPMatch(text, *usit);
		}
		cout << sum << endl;
		
		dict.clear();
	}
	
	return 0;
}