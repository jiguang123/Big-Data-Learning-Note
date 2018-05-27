//#define __MAIN__
#include <cstdio>
#include <cstdlib>
using namespace std;

class Solution {
public:
    int maxSubArray(int A[], int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
		if(A == nullptr){
			return 0;
		}

		if(n <= 0){
			return 0;
		}

		int i;
		int max_value;

		max_value = A[0];
		for(i = 0; i < n; ++i){
			if(A[i] > max_value){
				max_value = A[i];
			}
			if(A[i] >= 0){
				break;
			}
		}

		if(i >= n && max_value <= 0){
			// All A[i]s are 0 or negative.
			return max_value;
		}

		int sum, max_sum;

		sum = max_sum = 0;
		for(i = 0; i < n; ++i){
			sum += A[i];
			if(sum < 0){
				sum = 0;
			}
			if(sum > max_sum){
				max_sum = sum;
			}
		}

		return max_sum;
    }
};

#ifdef __MAIN__
int main()
{
	Solution sol;
	int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
	const int n = sizeof(A) / sizeof(int);

	printf("%d\n", sol.maxSubArray(A, n));

	return 0;
}
#endif