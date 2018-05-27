// 1CE, 6WA, 2RE, 1AC, seemed easy, proved to be tricky.
class Solution {
public:
    int calculateMinimumHP(vector<vector<int> > &dungeon) {
        int n, m;
        
        n = (int)dungeon.size();
        m = (int)dungeon[0].size();
        
        int i, j;
        vector<vector<int> > dp;
        
        dp.resize(n, vector<int>(m));
        dp[n - 1][m - 1] = min(1 - dungeon[n - 1][m - 1]);
        for (i = n - 2; i >= 0; --i) {
            dp[i][m - 1] = min(dp[i + 1][m - 1] - dungeon[i][m - 1]);
        }
        for (j = m - 2; j >= 0; --j) {
            dp[n - 1][j] = min(dp[n - 1][j + 1] - dungeon[n - 1][j]);
        }
        
        int s1, s2;
        for (i = n - 2; i >= 0; --i) {
            for (j = m - 2; j >= 0; --j) {
                s1 = dp[i][j + 1];
                s2 = dp[i + 1][j];
                dp[i][j] = min((s1 < s2 ? s1 : s2) - dungeon[i][j]);
            }
        }
        s1 = dp[0][0];
        for (i = 0; i < n; ++i) {
            dp[i].clear();
        }
        dp.clear();
        
        return s1;
    }
private:
    int min(int x) {
        return x <= 0 ? 1 : x;
    }
};