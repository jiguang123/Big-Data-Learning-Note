class Solution {
public:
    int removeElement(int A[], int n, int elem) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int i, j, k;
		int len;
		
		if(A == nullptr){
			return 0;
		}
		
		len = n;
		i = 0;
		j = n - 1;
		while(i <= j){ // BUG: j > i, fixed here
			if(A[i] == elem){
				while(j >= i){ // BUG: j > i, fixed here
					if(A[j] == elem){
						--j;
						--len;
					}else{
						A[i] = A[j];
						++i;
						--j;
						--len;
						break;
					}
				}
			}else{
				++i;
			}
		}
		
		return len;
    }
};