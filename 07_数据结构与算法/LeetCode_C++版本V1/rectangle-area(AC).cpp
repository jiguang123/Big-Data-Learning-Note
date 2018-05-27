// 1WA, 1AC
#include <algorithm>
using namespace std;

class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
		int I, J, K, L;
		
		I = max(A, E);
		J = max(B, F);
		K = min(C, G);
		L = min(D, H);
		K = max(I, K);
		L = max(J, L);
		return (C - A) * (D - B) + (G - E) * (H - F) - (K - I) * (L - J);
    }
};