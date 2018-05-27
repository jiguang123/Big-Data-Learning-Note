// 1AC, fast and clear, good work! O(n) complexity
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int i, j, len;
        int maxlen;
        
        len = s.length();
        if(len <= 1){
            return len;
        }
        
        // record the emergence of each alphabet
        int a[256];
        
        for(i = 0; i < 256; ++i){
            a[i] = 0;
        }
        
        ++a[s[0]];
        i = 0;
        j = 1;
        maxlen = j - i;
        while(true){
            if(i >= len){
                break;
            }
            while(j < len && a[s[j]] == 0){
                ++a[s[j]];
                ++j;
                if(j - i > maxlen){
                    maxlen = j - i;
                }
            }
            if(j >= len){
                break;
            }
            while(a[s[j]] > 0){
                --a[s[i]];
                ++i;
            }
        }
        return maxlen;
    }
};