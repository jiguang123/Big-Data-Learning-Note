// 1WA, 1AC
class Solution {
public:
    int removeDuplicates(int A[], int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
		int i, j, k;

		i = 0;
		k = 0;
		while(i < n){
			j = i + 1;
			while(j < n && A[i] == A[j]){
				++j;
			}
			// 1WA here, minor change in the if structure will do
			if(j > i + 1){
			    // if there're duplicates, allow one more duplicate
				A[k++] = A[i];
				A[k++] = A[i];
			}else{
			    A[k++] = A[i];
			}
			i = j;
		}

		return k;
    }
};
