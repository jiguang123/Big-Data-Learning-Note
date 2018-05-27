// 2CE, 1TLE, 1AC, simple online algorithm with O(n) time.
class Solution {
public:
	bool canJump(int A[], int n) {
		if (A == nullptr || n == 0) {
			return false;
		} else if (n == 1) {
			return true;
		}
		
		int ll, rr;
		
		rr = 0;
		for (ll = 0; ll < n; ++ll) {
			if (rr < ll) {
				// this position is unreachable
				// if this position is unreachable, so are all those behind it
				return false;
			} else {
				rr = mymax(rr, ll + A[ll]);
			}
		}
		
		return true;
	}
private:
	int mymax(const int x, const int y) {
		return (x > y ? x : y);
	}
};