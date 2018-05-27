// 1AC, next_permutation is handy~
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int> > permute(vector<int> &num) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
		for(int i = 0; i < result.size(); ++i){
			result[i].clear();
		}
		result.clear();

		int i;
		int n = num.size();
		int nn = 1;
		
		for(i = 1; i <= n; ++i){
			nn *= i;
		}
		
		for(i = 0; i < nn; ++i){
			result.push_back(vector<int>(num));
			next_permutation(num.begin(), num.end());
		}
		
		return result;
	}
private:
	vector<vector<int>> result;
};