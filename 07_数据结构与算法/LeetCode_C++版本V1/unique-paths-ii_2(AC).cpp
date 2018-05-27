// 1AC, very nice
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
		int flag = 0;
        
        arr = new int*[2];
        for(i = 0; i < 2; ++i){
            arr[i] = new int[n];
        }
        
		flag = 0;
        arr[flag][0] = obstacleGrid[0][0] ? 0 : 1;
        for(i = 1; i < n; ++i){
            arr[flag][i] = obstacleGrid[0][i] ? 0 : arr[flag][i - 1];
        }
        for(i = 1; i < m; ++i){
			flag = !flag;
			arr[flag][0] = obstacleGrid[i][0] ? 0 : arr[!flag][0];
            for(j = 1; j < n; ++j){
                arr[flag][j] = obstacleGrid[i][j] ? 0 : arr[!flag][j] + arr[flag][j - 1];
            }
        }
        
        j = arr[flag][n - 1];
        for(i = 0; i < 2; ++i){
            delete[] arr[i];
        }
        delete[] arr;
        
        return j;
    }
};