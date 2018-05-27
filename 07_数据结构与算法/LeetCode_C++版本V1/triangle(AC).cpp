// 4CE, 2WA, 1AC, calm down~
class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int n;
        vector<vector<int>> vv;
        int ff;
        
        n = triangle.size();
        if(n == 0){
            return 0;
        }
        
        int i, j;
        
        for(i = 0; i < 2; ++i){
            vv.push_back(vector<int>());
            for(j = 0; j < n; ++j){
                vv[i].push_back(0);
            }
        }
        
        ff = 0;
        vv[ff][0] = triangle[0][0];
        for(i = 1; i < n; ++i){
            vv[!ff][0] = vv[ff][0] + triangle[i][0];
            for(j = 1; j < i; ++j){
                // 2WA here, wrong coding
                vv[!ff][j] = mymin(vv[ff][j - 1], vv[ff][j]) + triangle[i][j];
            }
            // 4CE here, foolish coding!!!
            vv[!ff][i] = vv[ff][i - 1] + triangle[i][i];
            ff = !ff;
        }
        
        int res = vv[ff][0];
        for(i = 1; i < n; ++i){
            res = mymin(res, vv[ff][i]);
        }
        
        vv[0].clear();
        vv[1].clear();
        vv.clear();
        
        return res;
    }
private:
    const int mymin(const int &x, const int &y) {
        return (x < y ? x : y);
    }
};