// 1.5 Implement a method to perform basic string compression using the counts of repeated characters. For example, the string aabcccccaaa would become a2b1c5a3. If the compressed string  wouldn't become smaller than the original string, your method should return the original string.
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
	string compressString(const string str) {
		string res = "";
		
		int i, j;
		int len = (int)str.length();
		char tmp[50];

		i = 0;
		while (i < len) {
			j = i + 1;
			while (j < len && str[i] == str[j]) {
				++j;
			}
			sprintf(tmp, "%c%d", str[i], j - i);
			res = res + string(tmp);
			i = j;
		}
		
		if (res.length() < str.length()) {
			return res;
		} else {
			return str;
		}
	}
};

int main()
{
	string str;
	Solution sol;
	
	while (cin >> str) {
		cout << sol.compressString(str) << endl;
	}
	
	return 0;
}