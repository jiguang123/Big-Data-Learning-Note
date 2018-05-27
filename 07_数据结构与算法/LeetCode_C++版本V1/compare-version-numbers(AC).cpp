// 1CE, 3WA, 1AC, so boring.
class Solution {
public:
    int compareVersion(string version1, string version2) {
        splitNumber(version1, s1);
        splitNumber(version2, s2);
        normalize(s1);
        normalize(s2);
        
        int n1, n2, nm;
        
        n1 = (int)s1.size();
        n2 = (int)s2.size();
        nm = n1 < n2 ? n1 : n2;
        
        int i;
        int res;
        for (i = 0; i < nm; ++i) {
            res = compare(s1[i], s2[i]);
            if (res != 0) {
                return res;
            }
        }
        if (n1 > n2) {
            return 1;
        } else if (n1 < n2) {
            return -1;
        } else {
            return 0;
        }
    }
private:
    vector<string> s1, s2;
    
    void splitNumber(const string &s, vector<string> &ss) {
        int len = (int)s.length();
        int i, j, k;
        
        ss.clear();
        
        ss.push_back(string());
        i = 0;
        j = 0;
        k = 0;
        while (i < len) {
            if (s[i] == '.') {
                ss.push_back(string());
                ++k;
                j = 0;
            } else {
                ss[k].push_back(s[i]);
                ++j;
            }
            ++i;
        }
    }
    
    int compare(const string &n1, const string &n2) {
        if (n1.length() > n2.length()) {
            return 1;
        } else if (n1.length() < n2.length()) {
            return -1;
        }
        
        int i;
        int len = (int)n1.length();
        
        for (i = 0; i < len; ++i) {
            if (n1[i] > n2[i]) {
                return 1;
            } else if (n1[i] < n2[i]) {
                return -1;
            }
        }
        
        return 0;
    }
    
    string trimZero(const string &s) {
        int i, len;
        string s1;
        
        len = (int)s.length();
        i = 0;
        while (i < len - 1 && s[i] == '0') {
            ++i;
        }
        while (i < len) {
            s1.push_back(s[i]);
            ++i;
        }
        
        return s1;
    }
    
    void normalize(vector<string> &ss) {
        int i;
        int n = (int)ss.size();
        
        for (i = 0; i < n; ++i) {
            ss[i] = trimZero(ss[i]);
        }
        while (ss.size() > 1u && ss[ss.size() - 1] == "0") {
            ss.pop_back();
        }
    }
};