// 1WA, 1AC
class Solution {
public:
    int lengthOfLastWord(const char *s) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if(s == nullptr){
            return 0;
        }
        
        int len = strlen(s);
        
        if(len <= 0){
            return 0;
        }
        
        int i, j;
        
        i = len - 1;
        while(i >= 0 && s[i] == ' '){
            --i;
        }
        ++i;
        
        // 1WA, index is wrong, not j = i, but j = i - 1
        j = i - 1;
        while(j >= 0 && s[j] != ' '){
            --j;
        }
        ++j;
        if(i < 0 || j < 0 || i < j){
            return 0;
        }else{
            return i - j;
        }
    }
};