//1CE, 1RE, 1WA, 1AC
class Solution {
public:
    string intToRoman(int num) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.    
        string res;
        int a[4];
        
        a[0] = num % 10;
        num /= 10;
        a[1] = num % 10;
        num /= 10;
        a[2] = num % 10;
        num /= 10;
        a[3] = num % 10;
        num /= 10;
        
        res = "";
        //2WA here..
        /*
        for(int i = 0; i < 4; ++i){
            res += code[i][a[i]];
        }
        */
        /*
        for(int i = 3; i >= 0; ++i){
            res += code[i][a[i]];
        }
        */
        for(int i = 3; i >= 0; --i){
            res += code[i][a[i]];
        }
        
        return res;
    }
private:
    const string code[4][10] = {
        {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
        {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
        {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
        {"", "M", "MM", "MMM", "", "", "", "", "", ""}
    };
};