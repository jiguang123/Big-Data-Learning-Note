#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    string shortestPalindrome(string s) {
        next.clear();
        n = s.length();
        if (n == 0) {
            return "";
        }
        next.resize(n + 1);
        calcNext(s);
        
        int i, j, r;
        
        i = 0;
        j = n - 1;
        r = n - 1;
        while (i <= j) {
            if (s[i] == s[j]) {
                ++i;
                --j;
            } else if (next[i] == -1) {
                --j;
                r = j;
            } else {
                r = j + s[i];
                i = next[i];
            }
        }
        string s1 = s.substr(r + 1, s.length() - r - 1);
        reverse(s1.begin(), s1.end());
        return s1 + s;
    }
private:
    vector<int> next;
    int n;
    
    void calcNext(string &s) {
        int i = 0;
        int j = -1;
        next[0] = -1;
        while (i < n) {
            if (j == -1 || s[i] == s[j]) {
                ++i;
                ++j;
                next[i] = j;
            } else {
                j = next[j];
            }
        }
    }
};