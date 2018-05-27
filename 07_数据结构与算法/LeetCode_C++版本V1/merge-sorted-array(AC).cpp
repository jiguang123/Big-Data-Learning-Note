#include <algorithm>
using namespace std;

class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
		for(int i = m; i < m + n; ++i){
			A[i] = B[i - m];
		}
		sort(A, A + m + n);
    }
};