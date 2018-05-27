// Too careless, 2WA!!
class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
		result.clear();
		
		if(numRows <= 0){
			return result;
		}
		
		int i, j;
		for(i = 0; i < numRows; ++i){
			result.push_back(vector<int>());
			for(j = 0; j <= i; ++j){
				result[i].push_back(0);
			}
		}
		
		for(i = 0; i < numRows; ++i){
			result[i][i] = result[i][0] = 1;
		}
		
		for(i = 1; i < numRows; ++i){
			for(j = 1; j < i; ++j){
				result[i][j] = result[i - 1][j] + result[i - 1][j - 1];
			}
		}
		
		return result;
    }
private:
	vector<vector<int>> result;
};