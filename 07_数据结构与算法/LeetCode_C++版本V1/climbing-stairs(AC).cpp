class Solution {
public:
    int climbStairs(int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
		int f1, f2, f3;
		
		f1 = 0;
		f2 = 1;
		
		if(n <= 0){
			return 0;
		}
		
		for(int i = 0; i < n; ++i){
			f3 = f1 + f2;
			f1 = f2;
			f2 = f3;
		}
		
		return f3;
    }
};