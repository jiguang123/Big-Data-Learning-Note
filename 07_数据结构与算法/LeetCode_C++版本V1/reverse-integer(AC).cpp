class Solution {
public:
    int reverse(int x) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        long long int res, lx;

		if(x < 0){
			return -reverse(-x);
		}

		lx = x;
		res = 0;
		while(lx > 0){
			res = res * 10 + lx % 10;
			lx /= 10;
		}

		return res;
    }
};