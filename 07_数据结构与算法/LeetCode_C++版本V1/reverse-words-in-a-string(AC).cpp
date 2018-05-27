// 1TLE, 1AC, using another char[] is unnecessary. Don't miss '++i' or '++j'.
class Solution {
public:
    void reverseWords(string &s) {
		int i, j;
		int len;
		int offset;
		
		// remove trailing spaces
		while (s.length() > 0 && s[s.length() - 1] == ' ') {
			s.pop_back();
		}
		len = (int)s.length();
		if (len == 0) {
			return;
		}
		
		// remove leading spaces
		i = 0;
		while (i < len && s[i] == ' ') {
			++i;
		}
		s = s.substr(i, len - i);
		len = (int)s.length();
		
		// reverse the whole string
		reverse(s, 0, len - 1);
		// reverse every word
		i = 0;
		while (i < len) {
			j = i;
			while (j < len && s[j] != ' ') {
				++j;
			}
			reverse(s, i, j - 1);
			i = j;
			while (i < len && s[i] == ' ') {
				++i;
			}
		}
		
		// remove redundant spaces between words
		offset = 0;
		i = 0;
		while (true) {
			j = i;
			while (j < len && s[j] != ' ') {
				s[j - offset] = s[j];
				++j;
			}
			i = j;
			if (i == len) {
				break;
			}
			s[i - offset] = s[i];
			++i;
			while (i < len && s[i] == ' ') {
				++i;
				++offset;
			}
		}
		
		while (offset > 0) {
			s.pop_back();
			--offset;
		}
    }
private:
	void reverse(string &s, int ll, int rr) {
		int i;
		char ch;
		
		for (i = ll; i < ll + rr - i; ++i) {
			ch = s[i];
			s[i] = s[ll + rr - i];
			s[ll + rr - i] = ch;
		}
	}
};