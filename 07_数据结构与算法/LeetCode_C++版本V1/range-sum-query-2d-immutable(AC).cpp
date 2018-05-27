class NumMatrix {
public:
    NumMatrix(vector<vector<int>> &matrix) {
        vector<vector<int> > &a = matrix;
        n = a.size();
        m = n ? a[0].size() : 0;
        sum.resize(n + 1, vector<int>(m + 1, 0));
        
        int i, j;
        for (i = 1; i <= n; ++i) {
            for (j = 1; j <= m; ++j) {
                sum[i][j] = sum[i - 1][j] + sum[i][j - 1] + a[i - 1][j - 1] - sum[i - 1][j - 1];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return sum[row2 + 1][col2 + 1] + sum[row1][col1] - sum[row2 + 1][col1] - sum[row1][col2 + 1];
    }
protected:
    vector<vector<int> > sum;
    int n, m;
};
// Your NumMatrix object will be instantiated and called as such:
// NumMatrix numMatrix(matrix);
// numMatrix.sumRegion(0, 1, 2, 3);
// numMatrix.sumRegion(1, 2, 3, 4);