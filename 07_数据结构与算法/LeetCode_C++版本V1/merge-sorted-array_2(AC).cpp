// 1CE, 1AC, not bad, though~
#include <cstdlib>
using namespace std;

class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
		int *C = nullptr;
		
		if(nullptr == A || nullptr == B || m < 0 || n <= 0){
			// 1CE here, not 'return 0'
			return;
		}
		
		C = new(nothrow) int[m + n];
		if(nullptr == C){
			printf("Error: bad memory allocation.");
			exit(0);
		}
		int i, j, k;
		
		i = j = k = 0;
		while(i < m && j < n){
			if(A[i] < B[j]){
				C[k++] = A[i++];
			}else{
				C[k++] = B[j++];
			}
		}
		while(i < m){
			C[k++] = A[i++];
		}
		while(j < n){
			C[k++] = B[j++];
		}
		memcpy(A, C, (m + n) * sizeof(A[0]));
		delete[] C;
    }
};