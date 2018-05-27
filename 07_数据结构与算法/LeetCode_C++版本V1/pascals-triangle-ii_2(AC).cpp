// 1AC, excellent
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        result.clear();
        
        if(rowIndex < 0){
            return result;
        }
        
        long long int tmp;
        
        tmp = 1;
        result.push_back((int)tmp);
        for(int i = 1; i <= rowIndex; ++i){
            tmp = tmp * (rowIndex - i + 1) / i;
            result.push_back((int)tmp);
        }
        
        return result;
    }
private:
    vector<int> result;
};