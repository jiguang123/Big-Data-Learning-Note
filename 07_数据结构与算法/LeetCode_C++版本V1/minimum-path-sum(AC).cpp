// 1AC
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
		
		int **arr = new int*[m];
		int i, j;
		
		for(i = 0; i < m; ++i){
			arr[i] = new int[n];
		}
		
		arr[0][0] = grid[0][0];
		for(i = 1; i < m; ++i){
			arr[i][0] = arr[i - 1][0] + grid[i][0];
		}
		for(i = 1; i < n; ++i){
			arr[0][i] = arr[0][i - 1] + grid[0][i];
		}
		for(i = 1; i < m; ++i){
			for(j = 1; j < n; ++j){
				arr[i][j] = mymin(arr[i - 1][j], arr[i][j - 1]) + grid[i][j];
			}
		}
		
		j = arr[m - 1][n - 1];
		
		for(i = 0; i < m; ++i){
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