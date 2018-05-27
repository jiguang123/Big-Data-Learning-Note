// 1TLE, 1WA, 1AC, one-pass but inefficient solution
class Solution {
public:
    void sortColors(int A[], int n) {
        if(n <= 0 || A == nullptr){
            return;
        }
		
		int i0, i1, i2;
		int tmp;
		
		i0 = 0;
		i1 = n - 1;
		i2 = n - 1;
		// 1WA here, it's "<=" instead of "<".
		while(i0 <= i1){
			if(A[i0] == 1){
				tmp = A[i0];
				A[i0] = A[i1];
				A[i1] = tmp;
				--i1;
			}else if(A[i0] == 2){
				tmp = A[i0];
				A[i0] = A[i2];
				A[i2] = tmp;
				--i2;
				if(i2 < i1){
					//  1TLE here, it's "i1 = i2" instead of "i2 = i1".
					i1 = i2;
				}
			}else{
				++i0;
			}
		}
    }
};