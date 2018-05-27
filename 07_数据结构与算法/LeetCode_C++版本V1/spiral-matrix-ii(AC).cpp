// 4CE, 2RE, 1AC, such a terrible record..
class Solution {
public:
    vector<vector<int> > generateMatrix(int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        
        int i, j;
		// 1CE here, declaration for int i is missing
        for(i = 0; i < result.size(); ++i){
            result[i].clear();
        }
        result.clear();
        
		// 1RE here, special treatment for 0
        if(n <= 0){
            return result;
        }
        
        for(i = 0; i < n; ++i){
            result.push_back(vector<int>());
            for(j = 0; j < n; ++j){
                result[i].push_back(0);
            }
        }
        
		// 1CE here, declaration of d is missing
        int d, x, y, x1, y1, nn;
        nn = 1;
        x = 0;
        y = 0;
        d = RIGHT;
        while(true){
            result[x][y] = nn++;
			// 1RE here, judge statement should be put after nn++;
            if(nn > n * n){
                break;
            }
            while(true){
                x1 = x + dir[d][0];
                y1 = y + dir[d][1];
                if(x1 < 0 || x1 > n - 1 || y1 < 0 || y1 > n - 1 || result[x1][y1] > 0){
                    // already assigned
                    d = (d + 1) % 4;
                }else{
                    x = x1;
                    y = y1;
                    break;
                }
            }
        }
        
        return result;
    }
private:
    const int RIGHT = 0;
    const int DOWN = 1;
    const int LEFT = 2;
    const int UP = 3;
    int dir[4][2] = {
		// 1CE here, SBC case problem with comma...
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}
    };// 1CE here, semicolon missing
    vector<vector<int>> result;
};