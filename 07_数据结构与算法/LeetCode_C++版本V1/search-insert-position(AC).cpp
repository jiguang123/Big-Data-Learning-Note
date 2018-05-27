//#define __MAIN__
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
using namespace std;

class Solution {
public:
    int searchInsert(int A[], int n, int target) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
		if(n <= 0){
			return 0;
		}

		if(target < A[0]){
			return 0;
		}

		if(target > A[n - 1]){
			return n;
		}

		int ll, mm, rr;
		ll = 0;
		rr = n - 1;
		while(true){
			if(rr - ll <= 1){
				if(target == A[ll]){
					return ll;
				}else{
					return rr;
				}
			}
			mm = (ll + rr) / 2;
			if(target < A[mm]){
				rr = mm;
			}else if(target > A[mm]){
				ll = mm;
			}else{
				return mm;
			}
		}
		return rr;
    }
};

#ifdef __MAIN__
int main()
{
	Solution sol;
	int A[] = {1, 3, 5, 6};
	const int n = sizeof(A) / sizeof(int);
	int target;

	while(scanf("%d", &target) == 1){
		printf("%d\n", sol.searchInsert(A, n, target));
	}

	return 0;
}
#endif