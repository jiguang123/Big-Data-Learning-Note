//1RE, 1AC, special case needs special handling
class Solution {
public:
    string convert(string s, int nRows) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.    
		
		// 1RE here, ignored the special case where nRows == 1
		if(nRows == 1){
			return s;
		}
        char *str = nullptr;
		int i, j, k, len;
		
		len = s.length();
		str = new char[s.length() + 1];
		j = 0;
		for(k = 0; k < nRows; ++k){
			if(k == 0){
				for(i = 0; i < len; ++i){
					if(i % (2 * nRows - 2) == 0){
						str[j++] = s[i];
					}
				}
			}else if(k == nRows - 1){
				for(i = 0; i < len; ++i){
					if(i % (2 * nRows - 2) == nRows - 1){
						str[j++] = s[i];
					}
				}
			}else{
				for(i = 0; i < len; ++i){
					if(i % (2 * nRows - 2) == k || i % (2 * nRows - 2) == 2 * nRows - 2 - k){
						str[j++] = s[i];
					}
				}
			}
		}
		str[j] = 0;
		
		string res = string(str);
		delete[] str;
		return res;
    }
};