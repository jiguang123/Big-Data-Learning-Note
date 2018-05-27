// 1WA, 1AC, make sure you write good code.
class Solution {
public:
    int numDecodings(string s) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int a1, a2, a3;
        int i, n;
        
        n = s.length();
        if(n <= 0){
            return 0;
        }
        
        a1 = 1;
        if(s[n - 1] == '0'){
            a2 = 0;
        }else{
            a2 = 1;
        }
        for(i = n - 2; i >= 0; --i){
            if(s[i] == '0'){
                a3 = 0;
            }else{
                a3 = a2;
                if((s[i] - '0') * 10 + (s[i + 1] - '0') <= 26){
                    a3 += a1;
                }
            }
			a1 = a2;
			a2 = a3;
        }
        
		// 1WA here, 'return a2', not 'return a3'
        return a2;
    }
};