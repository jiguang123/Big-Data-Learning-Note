//#define __MAIN__
#include <cstdio>
#include <cstdlib>
using namespace std;

class Solution {
public:
    int removeDuplicates(int A[], int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
		int i, j, k;

		i = 0;
		k = 0;
		while(i < n){
			j = i + 1;
			while(j < n && A[i] == A[j]){
				++j;
			}
			A[k] = A[i];
			++k;
			i = j;
		}

		return k;
    }
};

#ifdef __MAIN__
int main()
{
	Solution sol;
	int A[] = {1};
	const int n = sizeof(A) / sizeof(int);
	int len;

	len = sol.removeDuplicates(A, n);
	printf("%d\n", len);
	for(int i = 0; i < len; ++i){
		printf("%d ", A[i]);
	}
	printf("\n");

	return 0;
}
#endif