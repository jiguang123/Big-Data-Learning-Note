// 1RE, 1AC
#include <algorithm>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int n = strs.size();
        // 1RE here, didn't consider the case when $strs is empty.
        if(n <= 0){
            return "";
        }
        string res = strs[0];
        
        int i;
        for(i = 1; i < n; ++i){
            res = commonPrefix(res, strs[i]);
            if(res == ""){
                break;
            }
        }
        
        return res;
    }
private:
    string commonPrefix(string s1, string s2) {
        if(s1.length() > s2.length()){
            return commonPrefix(s2, s1);
        }
        
        int len1, len2;
        
        len1 = s1.length();
        len2 = s2.length();
        int i;
        for(i = 0; i < len1; ++i){
            if(s1[i] != s2[i]){
                break;
            }
        }
        
        return s1.substr(0, i);
    }
};