// 1AC, not as efficient, but good solution
class Solution {
public:
    bool search(int A[], int n, int target) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int offset;
        
        if(A == nullptr || n <= 0){
            return false;
        }
        
        int left, mid, right;
        
        left = 0;
        right = n - 1;
        while(left <= right){
            mid = (left + right) / 2;
            // normal binary search cannot deal with cases like this
            // [2, 2, 0, 0, 2, 2, 2]
            if(A[left] < target && target < A[mid]){
                right = mid - 1;
            }else if(A[mid] < target && target < A[right]){
                left = mid + 1;
            }else{
                if(A[left] == target){
                    return true;
                }else{
                    ++left;
                }
                if(A[right] == target){
                    return true;
                }else{
                    --right;
                }
            }
        }
        
        return false;
    }
};