// 1CE, 1AC
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

typedef struct st{
public:
    string str;
    string sorted_str;
    
    st(string _str = "", string _sorted_str = "") {
        str = _str;
        sorted_str = _sorted_str;
    }
}st;

bool comparator(const st &x, const st &y)
{
    // 1CE here, return a.sorted_str < b.sorted_str;
    return x.sorted_str < y.sorted_str;
}

class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int max_len = 0;
        int i, j, n;
        char *ps = nullptr;
        
        result.clear();
        v.clear();
        
        n = strs.size();
        if(n <= 0){
            return result;
        }
        for(i = 0; i < n; ++i){
            if(strs[i].length() > max_len){
                max_len = strs[i].length();
            }
        }
        ps = new char[max_len + 1];
        
        string s, ss;
        for(i = 0; i < n; ++i){
            s = strs[i];
            strcpy(ps, s.data());
            sort(ps, ps + s.length());
            ss = string(ps);
            v.push_back(st(s, ss));
        }
        sort(v.begin(), v.end(), comparator);
        delete[] ps;
        i = 0;
        while(i < n){
            j = i;
            while(j < n && v[i].sorted_str == v[j].sorted_str){
                ++j;
            }
            if(j - i > 1){
                while(i < j){
                    result.push_back(v[i].str);
                    ++i;
                }
            }
            i = j;
        }
        v.clear();
        
        return result;
    }
private:
    vector<st> v;
    vector<string> result;
};