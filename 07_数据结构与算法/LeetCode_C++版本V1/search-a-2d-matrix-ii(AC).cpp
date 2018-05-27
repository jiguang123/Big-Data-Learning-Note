class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        vector<vector<int> > &a = matrix;
        int i, j;
        int n = a.size();
        int m = n ? a[0].size() : 0;
        
        i = 0;
        j = m - 1;
        // Here we presume there're no duplicates.
        while (i <= n - 1 && j >= 0) {
            if (target < a[i][j]) {
                --j;
            } else if (target > a[i][j]) {
                ++i;
            } else {
                return true;
            }
        }
        return false;
    }
};