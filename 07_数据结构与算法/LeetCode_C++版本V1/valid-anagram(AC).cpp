#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        int n = s.length();
        if (n != t.length()) {
            return false;
        }
        
        unordered_map<char, int> um;
        for (int i = 0; i < n; ++i) {
            ++um[s[i]];
            --um[t[i]];
        }
        for (auto it = um.begin(); it != um.end(); ++it) {
            if (it->second != 0) {
                return false;
            }
        }
        return true;
    }
};