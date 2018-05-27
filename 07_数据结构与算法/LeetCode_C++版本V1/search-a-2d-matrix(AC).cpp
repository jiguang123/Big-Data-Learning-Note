// 1AC, yeah~ 2D-address mapping on an array, then done with binary search. 
class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int m, n;
        int mn;
        
        m = matrix.size();
        if(m <= 0){
            return false;
        }
        
        n = matrix[0].size();
        if(n <= 0){
            return false;
        }
        
        mn = m * n;
        
        int left, mid, right;
        left = 0;
        right = mn - 1;
        while(right >= left){
            mid = (left + right) / 2;
            if(target > matrix[mid / n][mid % n]){
                left = mid + 1;
            }else if(target < matrix[mid / n][mid % n]){
                right = mid - 1;
            }else{
                return true;
            }
        }
        
        return false;
    }
};