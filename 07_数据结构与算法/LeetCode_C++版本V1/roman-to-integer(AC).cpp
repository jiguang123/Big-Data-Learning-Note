class Solution {
public:
    int romanToInt(string s) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
		int i, len;
		int res;
		
		b['I'] = 1;
		b['V'] = 5;
		b['X'] = 10;
		b['L'] = 50;
		b['C'] = 100;
		b['D'] = 500;
		b['M'] = 1000;

		res = 0;
		i = 0;
		len = s.length();
		while(i < len){
			if(i < len - 1){
				if(b[s[i]] < b[s[i + 1]]){
					res += b[s[i + 1]] - b[s[i]];
					i += 2;
				}else{
					res += b[s[i]];
					++i;
				}
			}else{
				res += b[s[i]];
				++i;
			}
		}
		
		return res;
    }
private:
	int b[128];
};