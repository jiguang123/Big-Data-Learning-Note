#include <cstring>
using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        return check(s, t) && check(t, s);
    }
private:
    bool check(string s, string t) {
        char a[256];
        
        memset(a, 0, sizeof(a));
        int i;
        int n = s.length();
        
        for (i = 0; i < n; ++i) {
            if (a[s[i]] == 0) {
                a[s[i]] = t[i];
            }
            s[i] = a[s[i]];
        }
        
        return s == t;
    }
};