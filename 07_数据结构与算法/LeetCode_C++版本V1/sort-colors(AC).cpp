// 1WA, 1AC
class Solution {
public:
    void sortColors(int A[], int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if(n <= 0 || A == nullptr){
            return;
        }
        
        int n0, n1, n2;
        int i, j;
        
        // 1WA here, wrong sentence: n0 = n1 = n2;
        n0 = n1 = n2 = 0;
        for(i = 0; i < n; ++i){
            if(A[i] == 0){
                ++n0;
            }else if(A[i] == 1){
                ++n1;
            }else{
                ++n2;
            }
        }
        
        j = 0;
        for(i = 0; i < n0; ++i){
            A[j++] = 0;
        }
        for(i = 0; i < n1; ++i){
            A[j++] = 1;
        }
        for(i = 0; i < n2; ++i){
            A[j++] = 2;
        }
    }
};