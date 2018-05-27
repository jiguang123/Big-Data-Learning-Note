// 1AC, very nice~
class Solution {
public:
    int numDecodings(string s) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int *a;
        int i, n;
        
        n = s.length();
        if(n <= 0){
            return 0;
        }
        a = new int[n + 1];
        
        a[0] = 1;
        if(s[n - 1] == '0'){
            a[1] = 0;
        }else{
            a[1] = 1;
        }
        for(i = n - 2; i >= 0; --i){
            if(s[i] == '0'){
                a[n - i] = 0;
            }else{
                a[n - i] = a[n - i - 1];
                if((s[i] - '0') * 10 + (s[i + 1] - '0') <= 26){
                    a[n - i] += a[n - i - 2];
                }
            }
        }
        
        n = a[n];
        delete[] a;
        return n;
    }
};