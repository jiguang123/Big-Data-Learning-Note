// 2WA, 1AC, fair enough~
// #define MY_MAIN
// A line other than the last line might contain only one word. What should you do in this case?
// In this case, that line should be left-justified.
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string> &words, int L) {
		int ll, rr;
		int i, j;
		int wc = (int)words.size();
		int total_len;
		int space_len1, space_len2;
		int space_count1, space_count2;
		int len;
		
		result.clear();
		// 1WA here, special case is dealt with here.
		if (wc == 1) {
			s[0] = 0;
			sprintf(s, "%s", words[0].c_str());
			len = (int)words[0].length();
			while (len < L) {
				s[len++] = ' ';
			}
			s[len] = 0;
			result.push_back(string(s));
			return result;
		}
		
		ll = 0;
		while (ll < wc) {
			rr = ll + 1;
			total_len = (int)words[ll].length();
			while (rr < wc && total_len + 1 + (int)words[rr].length() <= L) {
				total_len += ((int)words[rr].length() + 1);
				++rr;
			}
			
			if (rr < wc) {
				// the total length exceeds L, more lines to be expected
				// fully-justified
				total_len -= (rr - ll - 1);
				if (rr - ll > 1) {
					space_count1 = (L - total_len) % (rr - ll - 1);
					space_count2 = (rr - ll - 1) - space_count1;
					space_len1 = (L - total_len) / (rr - ll - 1) + 1;
					space_len2 = (L - total_len) / (rr - ll - 1);
					s[0] = 0;
					sprintf(s, "%s", words[ll].c_str());
					len = (int)words[ll].length();
					for (i = 0; i < space_count1; ++i) {
						for (j = 0; j < space_len1; ++j) {
							s[len++] = ' ';
						}
						s[len] = 0;
						sprintf(s + len, "%s", words[ll + 1 + i].c_str());
						len += words[ll + 1 + i].length();
					}
					for (i = 0; i < space_count2; ++i) {
						for (j = 0; j < space_len2; ++j) {
							s[len++] = ' ';
						}
						s[len] = 0;
						sprintf(s + len, "%s", words[ll + 1 + space_count1 + i].c_str());
						len += words[ll + 1 + space_count1 + i].length();
					}
				} else {
					// only one word on this line, and not the last line
					// left-justified
					s[0] = 0;
					sprintf(s, "%s", words[ll].c_str());
					for (i = (int)words[ll].length(); i < L; ++i) {
						s[i] = ' ';
					}
					s[i] = 0;
				}
			} else {
				// the last line is reached
				// left-justified
				s[0] = 0;
				sprintf(s, "%s", words[ll].c_str());
				len = (int)words[ll].length();
				for (i = ll + 1; i < rr; ++i) {
					s[len++] = ' ';
					s[len] = 0;
					sprintf(s + len, "%s", words[i].c_str());
					len += (int)words[i].length();
				}
				// 1WA here, the last line must be filled with spaces.
				while (len < L) {
					s[len++] = ' ';
				}
				s[len] = 0;
			}
			result.push_back(string(s));
			ll = rr;
		}
		
		return result;
    }
private:
	char s[10000];
	vector<string> result;
};

#ifdef MY_MAIN
int main()
{
	int i;
	int n;
	vector<string> words;
	int L;
	char s[1000];
	Solution solution;
	vector<string> result;
	
	while (scanf("%d", &n) == 1 && n) {
		scanf("%d", &L);
		words.clear();
		for (i = 0; i < n; ++i) {
			scanf("%s", s);
			words.push_back(string(s));
		}
		result = solution.fullJustify(words, L);
		for (i = 0; i < (int)result.size(); ++i) {
			printf("%d: %s\n", i + 1, result[i].c_str());
		}
	}
	
	return 0;
}
#endif