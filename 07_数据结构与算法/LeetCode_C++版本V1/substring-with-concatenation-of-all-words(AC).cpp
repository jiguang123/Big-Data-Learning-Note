#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
	vector<int> findSubstring(string S, vector<string> &L) {
		vector<int> result_set;
		vector<int> vi;
		vector<int> vic;
		unordered_map<string, int> um;
		unordered_map<string, int>::iterator uit;
		int wl;
		int nc;
		int n = (int)L.size();
		int slen = (int)S.length();
		
		if (slen == 0 || n == 0) {
			return result_set;
		}
		wl = (int)L[0].length();
		if (wl == 0) {
			return result_set;
		}
		if (slen < n * wl) {
			return result_set;
		}
		
		um.clear();
		vi.clear();
		nc = 0;
		
		int i, j;
		for (i = 0; i < n; ++i) {
			uit = um.find(L[i]);
			if (uit == um.end()) {
				um[L[i]] = nc;
				vi.push_back(1);
				++nc;
			} else {
				++vi[um[L[i]]];
			}
		}
		vic.resize(nc);
		
		int cc, ll, rr;
		int idx;
		string str;
		
		for (i = 0; i < wl; ++i) {
			for (j = 0; j < nc; ++j) {
				vic[j] = vi[j];
			}
			cc = 0;
			
			ll = i;
			rr = ll;
			while (rr + wl <= slen) {
				str = S.substr(rr, wl);
				uit = um.find(str);
				if (uit != um.end()) {
					idx = uit->second;
					if (vic[idx] == 0) {
						while (true) {
							str = S.substr(ll, wl);
							if (um[str] != idx) {
								ll += wl;
								++vic[um[str]];
								--cc;
							} else {
								ll += wl;
								++vic[um[str]];
								--cc;
								break;
							}
						}
					} else {
						--vic[idx];
						++cc;
						rr += wl;
					}
				} else {
					ll = rr + wl;
					for (j = 0; j < nc; ++j) {
						vic[j] = vi[j];
					}
					rr = ll;
					cc = 0;
				}
				if (cc == n) {
					result_set.push_back(ll);
					str = S.substr(ll, wl);
					idx = um[str];
					++vic[idx];
					--cc;
					ll += wl;
				}
			}
		}
		vic.clear();
		
		return result_set;
	}
};