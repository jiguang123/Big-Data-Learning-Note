class Solution {
public:
    int numTrees(int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        // res = C(2 * n, n) / (n + 1)
		return combination(2 * n, n) / (n + 1);
    }
private:
	int combination(int n, int k) {
		int i;
		int res, quo;
		
		if(k > n / 2){
			return combination(n, n - k);
		}

		res = quo = 1;
		for(i = 1; i <= k; ++i){
			res *= (n + 1 - i);
			quo *= i;
			if(res % quo == 0){
				res /= quo;
				quo = 1;
			}
		}

		return res;
	}
};