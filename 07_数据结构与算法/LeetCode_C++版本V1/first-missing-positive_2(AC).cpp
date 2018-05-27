// 1CE, 1AC, this solution is very tricky, hope it would inspire you.
class Solution {
public:
	int firstMissingPositive(int A[], int n) {
		if (A == nullptr || n <= 0) {
			return 1;
		}
		
		int i;
		for (i = 0; i < n; ++i) {
			if (A[i] <= 0) {
				A[i] = n + 1;
			}
		}
		
		int tmp;
		for (i = 0; i < n; ++i) {
			if (myabs(A[i]) <= n) {
				// think about why we care about values between [1, n]
				tmp = myabs(A[i]);
				// the array itself serves as a hash table of size n.
				// setting it to minus means occupying this position.
				A[tmp - 1] = -myabs(A[tmp - 1]);
			}
		}
		
		for (i = 0; i < n; ++i) {
			if (A[i] > 0) {
				return (i + 1);
			}
		}
		// this array consists of [1, n].
		return (n + 1);
	}
private:
	int myabs(const int x) {
		return (x >= 0 ? x : -x);
	}
};