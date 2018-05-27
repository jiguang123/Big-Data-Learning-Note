// 2CE, 1RE, 1WA, 1AC, KMP Algorithm
#include <cstring>
#include <vector>
using namespace std;

class Solution {
public:
    char *strStr(char *haystack, char *needle) {
		if (haystack == nullptr || needle == nullptr) {
			return nullptr;
		}
		lp = strlen(needle);
		lw = strlen(haystack);
		
		if (lp == 0) {
			return haystack;
		}
		
		if (lw < lp) {
			return nullptr;
		}
		
		calculateNext(needle);
		char *result = KMPMatch(haystack, needle);
		next.clear();
		
		return result;
    }
private:
	int lp;
	int lw;
	vector<int> next;
	
	void calculateNext(char *pat) {
		int i = 0;
		int j = -1;
		
		next.resize(lp + 1);
		next[0] = -1;
		while (i < lp) {
			if (j == -1 || pat[i] == pat[j]) {
				++i;
				++j;
				next[i] = j;
			} else {
				j = next[j];
			}
		}
	}
	
	char* KMPMatch(char *word, char *pat)
	{
		int index;
		int pos;
		
		index = pos = 0;
		while (index < lw) {
			if (pos == -1 || word[index] == pat[pos]) {
				++index;
				++pos;
			} else {
				pos = next[pos];
			}
			
			if (pos == lp) {
				// the first match is found
				return word + (index - lp);
			}
		}
		
		return nullptr;
	}
};