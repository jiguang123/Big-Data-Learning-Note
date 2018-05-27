// 1AC, the brute-force solution, O(n^2) time complexity
class Solution {
public:
    string longestPalindrome(string s) {
        int i, j;
        int len;
        int ll, rr;
        string s1, s2;
        string str;
        
        len = (int)s.length();
        if (len <= 1) {
            return s;
        }
        s1 = "";
        for (i = 0; i < len; ++i) {
            j = 0;
            while (true) {
                if ((i - j < 0) || (i + j > len - 1) || (s[i - j] != s[i + j])) {
                    break;
                } else {
                    ++j;
                }
            }
            --j;
            if (2 * j + 1 > (int)s1.length()) {
                s1 = s.substr(i - j, 2 * j + 1);
            }
        }
        s2 = "";
        for (i = 0; i < len - 1; ++i) {
            j = 0;
            while (true) {
                if ((i - j < 0) || (i + 1 + j > len - 1) || (s[i - j] != s[i + 1 + j])) {
                    break;
                } else {
                    ++j;
                }
            }
            --j;
            if (2 * j + 2 > (int)s2.length()) {
                s2 = s.substr(i - j, 2 * j + 2);
            }
        }
        
        if (s1.length() > s2.length()) {
            return s1;
        } else {
            return s2;
        }
    }
};