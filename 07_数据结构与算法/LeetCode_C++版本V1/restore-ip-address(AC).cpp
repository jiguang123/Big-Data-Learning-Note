//#define __MAIN__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
	vector<string> restoreIpAddresses(string s) {
		// Note: The Solution object is instantiated only once and is reused by each test case.
		str = s.data();
		slen = strlen(str);
		res.clear();
		if(slen > 12){
			return res;
		}
		dfs(0, 0);
		
		return res;
	}
private:
	int slen;
	int a[4];
	vector<string> res;
	const char *str;
	char tmp[100];

	void dfs(int si, int ai) {
		int i;
		int num;
		string snum;
		
		if(ai == 4){
			if(si == slen){
				sprintf(tmp, "%d.%d.%d.%d", a[0], a[1], a[2], a[3]);
				res.push_back(string(tmp));
			}
			return;
		}
		
		if(si >= slen){
			return;
		}
		
		if(ai + (slen - si) / 3 > 4){
			return;
		}
		
		num = 0;
		snum = "";
		for(i = si; i < si + 3 && i < slen; ++i){
			if(snum.length() > 0 && snum[0] == '0'){
				//cannot add more digits after leading 0
				break;
			}
			num = num * 10 + (str[i] - '0');
			snum = snum + str[i];
			if(num > 255){
				break;
			}else{
				a[ai] = num;
				dfs(i + 1, ai + 1);
			}
		}
	}
};

#ifdef __MAIN__
#include <iostream>
int main()
{
	Solution sol;
	char str[100];
	vector<string> res;
	int i;

	while(gets(str) != NULL){
		res = sol.restoreIpAddresses(string(str));
		cout << "res_count = " << res.size() << endl;
		for(i = 0; i < res.size(); ++i){
			cout << res[i] << endl;
		}
		cout << endl;
	}

	return 0;
}
#endif