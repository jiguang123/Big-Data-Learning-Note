// 1CE 2WA 1AC, you fool..
// Too careless!!!
class Solution {
public:
    vector<int> grayCode(int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
		vector<int> res1, res2;
		res1.clear();
		res2.clear();
		
		if(n < 0){
			return res1;
		}
		
		int nn = 1 << n;
		int i, j;
		
		res1.push_back(0);
		for(i = 1; i <= n; ++i){
			nn = 1 << (i - 1);
			for(j = 0; j < nn; ++j){
				res2.push_back(res1[j]);
			}
			for(j = nn - 1; j >= 0; --j){
				res2.push_back(nn + res1[j]);
			}
			res1 = res2;
			res2.clear();
		}
		
		return res1;
    }
};