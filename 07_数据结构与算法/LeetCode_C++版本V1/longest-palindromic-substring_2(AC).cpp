// 1CE, 2WA, 1AC, this really wasn't easy to understand..
class Solution {
public:
    string longestPalindrome(string s) {
        int len = (int)s.length();
        int nlen;
        int i, j;
        char *ss;
        int *p;
        
        nlen = 2 * len + 2;
        ss = new char[nlen + 1];
        p = new int[nlen + 1];
        
        // insert '#' between every character.
        nlen = 0;
        ss[nlen++] = '$';
        for (i = 0; i < len; ++i) {
            ss[nlen++] = '#';
            ss[nlen++] = s[i];
        }
        ss[nlen++] = '#';
        ss[nlen] = 0;
        
        // the farthest position the current palindromic string can reach.
        int mx_pos;
        // the index i that reaches this farthest position.
        int id;
        
        // the Manacher algorithm
        p[0] = 0;
        mx_pos = 0;
        for (i = 1; i < nlen; ++i) {
            p[i] = 1;
            if (mx_pos > i) {
                p[i] = p[2 * id - i];
                if (mx_pos - i < p[i]) {
                    p[i] = mx_pos - i;
                }
            }
            
            while (ss[i - p[i]] == ss[i + p[i]]) {
                ++p[i];
            }
            
            if (i + p[i] > mx_pos) {
                mx_pos = i + p[i];
                id = i;
            }
        }
        
        // find the maximal value
        int result = 0;
        int ri;
        string res_str;
        char *res;
        res = new char[len + 1];
        for (i = 0; i < nlen; ++i) {
            if (p[i] > result) {
                ri = i;
                result = p[i];
            }
        }
        
        len = 0;
        for (i = ri - p[ri] + 1; i <= ri + p[ri] - 1; ++i) {
            if ((i > 0) && ((i & 0x1) == 0)) {
                // odd positions are inserted with '#'
                // 0th position is inserted with '$'
                res[len++] = ss[i];
            }
        }
        res[len] = 0;
        res_str = string(res);
        
        delete [] res;
        delete [] p;
        delete [] ss;
        
        return res_str;
    }
};