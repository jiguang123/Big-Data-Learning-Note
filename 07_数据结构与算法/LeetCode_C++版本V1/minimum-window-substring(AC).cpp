// 4CE, 5WA, 1AC, O(n) solution, mein Gott (O_o)(>_<)(u_u)(x_X)
class Solution {
public:
	string minWindow(string S, string T) {
		int i;
		int tc[256];
		int c[256];
		int cc;
		int slen, tlen;
		int ll, rr;
		int mll, mrr;
		
		slen = (int)S.length();
		tlen = (int)T.length();
		if (slen == 0 || tlen == 0 || slen < tlen) {
			return "";
		}
		
		for (i = 0; i < 256; ++i) {
			c[i] = 0;
			tc[i] = 0;
		}
		
		for (i = 0; i < tlen; ++i) {
			++tc[T[i]];
		}
		cc = 0;
		
		mll = -1;
		mrr = -1;
		ll = 0;
		while (ll < slen && tc[S[ll]] == 0) {
			// skip irrelavant letters
			++ll;
		}
		if (ll == slen) {
			// S and T have no letters in common
			return "";
		}
		
		rr = ll;
		while (rr < slen) {
			++c[S[rr]];
			if (c[S[rr]] <= tc[S[rr]]) {
				// S = caae, T = cae
				// the window may contain redundant letters in T
				++cc;
			}
			
			while (cc == tlen) {
				if (mll == -1 || (rr - ll + 1) < (mrr - mll + 1)) {
					// a better result is found
					mll = ll;
					mrr = rr;
				}
				// move ll to right
				--c[S[ll]];
				if (c[S[ll]] < tc[S[ll]]) {
					--cc;
				}
				++ll;
				
				while (ll < slen && tc[S[ll]] == 0) {
					// skip irrelavant letters
					++ll;
				}
				if (rr < ll) {
					// ll must not go over rr
					rr = ll;
				}
			}
			++rr;
			while (rr < slen && tc[S[rr]] == 0) {
				++rr;
			}
		}
		
		if (mll == -1) {
			return "";
		} else {
			return S.substr(mll, mrr - mll + 1);
		}
	}
};