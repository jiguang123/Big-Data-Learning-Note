// 1AC, in a real interview, this could be difficult.
#include <cctype>
#include <vector>
using namespace std;

typedef long long int LL;

class Solution {
public:
	Solution() {
		// Defining a precedence level is smarter than hard coding.
		// Here I presume the operators are all one-character long.
		int p = -1;
		
		// Think about why.
		pre['('] = p;
		++p;
		
		pre['&'] = p;
		pre['|'] = p;
		pre['^'] = p;
		++p;
		
		pre['+'] = p;
		pre['-'] = p;
		++p;
		
		pre['*'] = p;
		pre['/'] = p;
		pre['%'] = p;
		++p;
	}
	
	int calculate(string s) {
		s = noSpace(s);
		
		int i, j;
		int n = s.length();
		int val;
		
		i = 0;
		while (i < n) {
			if (isdigit(s[i])) {
				val = 0;
				j = i;
				while (j < n && isdigit(s[j])) {
					val = val * 10 + (s[j++] - '0');
				}
				num.push_back(val);
				i = j;
				continue;
			}
			switch (s[i]) {
			case '+':
			case '-':
			case '*':
			case '/':
				while (!op.empty() && pre[op.back()] >= pre[s[i]]) {
					calc();
				}
				op.push_back(s[i]);
				break;
			case '(':
				op.push_back(s[i]);
				break;
			case ')':
				while (op.back() != '(') {
					calc();
				}
				op.pop_back();
				break;
			}
			++i;
		}
		
		while (num.size() > 1) {
			calc();
		}
		val = num.back();
		num.clear();
		op.clear();
		
		return val;
	}
private:
	int pre[256];
	vector<LL> num;
	vector<char> op;
	
	string noSpace(string &s) {
		string ss = "";
		int n = s.length();
		int i;
		for (i = 0; i < n; ++i) {
			if (s[i] == ' ') {
				continue;
			}
			ss.push_back(s[i]);
		}
		return ss;
	}
	
	void calc() {
		LL v1, v2, v3;
		
		v2 = num.back();
		num.pop_back();
		v1 = num.back();
		num.pop_back();
		
		switch (op.back()) {
		case '+':
			v3 =  v1 + v2;
			break;
		case '-':
			v3 = v1 - v2;
			break;
		case '*':
			v3 = v1 * v2;
			break;
		case '/':
			v3 = v1 / v2;
			break;
		}
		op.pop_back();
		num.push_back(v3);
	}
};