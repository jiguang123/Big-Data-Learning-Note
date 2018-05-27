// 1WA, 1AC, could've been perfect
class Solution {
public:
	int minPathSum(vector<vector<int> > &grid) {
		// IMPORTANT: Please reset any member data you declared, as
		// the same Solution instance will be reused for each test case.
		int m, n;
		
		m = grid.size();
		if(m <= 0){
			return 0;
		}
		
		n = grid[0].size();
		if(n <= 0){
			return 0;
		}
		
		int **arr = new int*[2];
		int i, j;
		int flag;
		
		for(i = 0; i < 2; ++i){
			arr[i] = new int[n];
		}
		
		flag = 0;
		arr[flag][0] = grid[0][0];
		for(i = 1; i < n; ++i){
			arr[flag][i] = arr[flag][i - 1] + grid[0][i];
		}
		for(i = 1; i < m; ++i){
			flag = !flag;
			// 1WA here, forgot to add grid[i][0]
			arr[flag][0] = arr[!flag][0] + grid[i][0];
			for(j = 1; j < n; ++j){
				arr[flag][j] = mymin(arr[!flag][j], arr[flag][j - 1]) + grid[i][j];
			}
		}
		
		j = arr[flag][n - 1];
		
		for(i = 0; i < 2; ++i){
			delete[] arr[i];
		}
		delete[] arr;
		return j;
	}
private:
	const int &mymin(const int &x, const int &y) {
		return (x < y ? x : y);
	}
};