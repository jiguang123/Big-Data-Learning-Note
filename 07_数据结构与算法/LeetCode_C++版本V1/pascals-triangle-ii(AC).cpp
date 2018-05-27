// 1RE, 1AC
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        
        int i, j;
        result.clear();
        result.push_back(1);
        for(i = 0; i < rowIndex; ++i){
            tmp.push_back(1);
            for(j = 1; j <= i; ++j){
				// tmp[j] = result[j - 1] + result[j];
				// 1RE here, you haven't even pushed, how do you tmp[j] anyway???
                tmp.push_back(result[j - 1] + result[j]);
            }
            tmp.push_back(1);
            result = tmp;
            tmp.clear();
        }
        
        return result;
    }
private:
    vector<int> result, tmp;
};