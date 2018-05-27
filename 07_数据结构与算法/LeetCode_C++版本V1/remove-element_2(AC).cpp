class Solution {
public:
    int removeElement(int A[], int n, int elem) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int i, j;
		int len;
		
		if(A == nullptr){
			return 0;
		}
		
		len = n;
		i = 0;
		j = 0;
		while(i < n){
			if(A[i] == elem){
				--len;
				++i;
			}else{
				A[j++] = A[i++];
			}
		}
		
		return len;
    }
};