// 1RE, 1AC, be more careful, could've 1AC~
class Solution {
public:
    bool isPalindrome(string s) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int i, j, len;
        
        len = s.length();
        if(len <= 0){
            return true;
        }
        
        char a, b;
        
        i = 0;
        j = len - 1;
        while(i < j){
            if(s[i] >= 'a' && s[i] <= 'z'){
                a = s[i];
            }else if(s[i] >= '0' && s[i] <= '9'){
                a = s[i];
            }else if(s[i] >= 'A' && s[i] <= 'Z'){
                a = s[i] - 'A' + 'a';
            }else{
                ++i;
                continue;
            }
            if(s[j] >= 'a' && s[j] <= 'z'){
                b = s[j];
            }else if(s[j] >= '0' && s[j] <= '9'){
                b = s[j];
            }else if(s[j] >= 'A' && s[j] <= 'Z'){
                b = s[j] - 'A' + 'a';
            }else{
                // 1RE here, wrong direction of $j
                --j;
                continue;
            }
            if(a == b){
                ++i;
                --j;
            }else{
                break;
            }
        }
        
        return i >= j;
    }
};