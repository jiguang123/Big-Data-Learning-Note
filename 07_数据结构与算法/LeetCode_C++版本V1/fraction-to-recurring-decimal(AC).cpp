// 1RE, 1TLE, 3MLE, 1AC, watch out for boundary cases and memory limit
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

typedef long long int ll;

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
		ll n = numerator;
		ll d = denominator;

		int sn, sd;

		sn = n >= 0 ? 1 : -1;
		n = n >= 0 ? n : -n;
		sd = d >= 0 ? 1 : -1;
		d = d >= 0 ? d : -d;

		if (n == 0) {
			return "0";
		}

		string res = "";
		if (sn * sd < 0) {
			res.push_back('-');
		}

		ll q = n / d;
		ll r = n % d;

		res += to_string(q);

		if (r == 0) {
			return res;
		}

		res.push_back('.');
		int pos = (int)res.length();

	    unordered_map<ll, int> seq;
		unordered_map<ll, int>::iterator it;

		while (r != 0) {
			it = seq.find(r);
			if (it != seq.end()) {
				res.insert(it->second, "(");
				res.push_back(')');
				return res;
			}
			seq[r] = pos;
			q = r * 10 / d;
			r = r * 10 % d;
			res.push_back((int)q + '0');
			++pos;
		}

		seq.clear();
		return res;
    }
private:
};
/*
int main()
{
	int n, d;
	Solution sol;

	while (cin >> n >> d) {
		cout << sol.fractionToDecimal(n, d) << endl;
	}

	return 0;
}
*/