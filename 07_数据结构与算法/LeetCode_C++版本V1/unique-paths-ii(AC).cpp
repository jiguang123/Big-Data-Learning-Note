// 1WA, 1AC
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int m, n;
        
        m = obstacleGrid.size();
        if(m <= 0){
            return 0;
        }
        
        n = obstacleGrid[0].size();
        
        int **arr = nullptr;
        int i, j;
        
        arr = new int*[m];
        for(i = 0; i < m; ++i){
            arr[i] = new int[n];
        }
        
        arr[0][0] = obstacleGrid[0][0] ? 0 : 1;
        for(i = 1; i < m; ++i){
            // 1WA here, arr[i][0] = obstacleGrid[i][0] ? 0 : obstacleGrid[i - 1][0];
            // arr[i][0] = obstacleGrid[i][0] ? 0 : arr[i - 1][0];
            arr[i][0] = obstacleGrid[i][0] ? 0 : arr[i - 1][0];
        }
        for(i = 1; i < n; ++i){
            arr[0][i] = obstacleGrid[0][i] ? 0 : arr[0][i - 1];
        }
        for(i = 1; i < m; ++i){
            for(j = 1; j < n; ++j){
                arr[i][j] = obstacleGrid[i][j] ? 0 : arr[i - 1][j] + arr[i][j - 1];
            }
        }
        
        int res = arr[m - 1][n - 1];
        for(i = 0; i < m; ++i){
            delete[] arr[i];
        }
        delete[] arr;
        
        return res;
    }
};