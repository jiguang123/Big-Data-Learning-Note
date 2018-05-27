#define __MAIN__
#ifdef __MAIN__
#include <string>
using namespace std;
#endif

class Solution {
public:
    string addBinary(string a, string b) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
		if(a.length() < b.length()){
			return addBinary(b, a);
		}
		
		if(a == "0"){
		    return b;
		}else if(b == "0"){
			return a;
		}
		
		int i;
		char *buf = nullptr, tmp;
		int lena, lenb;
		
		lena = a.length();
		lenb = b.length();
		buf = new char[lena + 2];
		for(i = 0; i < lena + 2; ++i){
			buf[i] = 0;
		}
		for(i = 0; i < lena; ++i){
			buf[i] += (a[lena - 1 - i] - '0');
		}
		for(i = 0; i < lenb; ++i){
			buf[i] += (b[lenb - 1 - i] - '0');
		}
		for(i = 0; i < lena + 1; ++i){
			buf[i + 1] += buf[i] / 2;
			buf[i] %= 2;
		}
		for(i = 0; i < lena + 1; ++i){
			buf[i] += '0';
		}
		for(i = 0; i < lena - i; ++i){
			tmp = buf[i];
			buf[i] = buf[lena - i];
			buf[lena - i] = tmp;
		}
		
		string res;
		if(buf[0] > '0'){
			res = string(buf);
		}else{
			res = string(buf + 1);
		}
		delete[] buf;
		
		return res;
    }
};