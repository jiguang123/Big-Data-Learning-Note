// 1CE, 1AC
#include <cstdio>
using namespace std;

class Solution {
public:
    string countAndSay(int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        string res = "1";
        
        for(int i = 1; i < n; ++i){
            res = nextSequence(res);
        }
        
        return res;
    }
private:
    char buf[100];
    string nextSequence(string cur) {
        string res;
        int i, j;
        int len = cur.length();
        
        res = "";
        i = 0;
        while(i < len){
            j = i + 1;
            while(j < len && cur[i] == cur[j]){
                ++j;
            }
            // 1CE here, you can't simply concatenate string with other data type...
            // use sprintf or sstream to do this
            sprintf(buf, "%d%c", j - i, cur[i]);
            res = res + string(buf);
            i = j;
        }
        
        
        return res;
    }
};