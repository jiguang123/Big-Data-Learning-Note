// 1RE 1AC
class Solution {
public:
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
		merge(A, m, B, n);
		if((m + n) % 2 == 1){
			return C[(m + n - 1) / 2];
		}else{
			return (C[(m + n) / 2 - 1] + C[(m + n) / 2]) / 2.0;
		}
    }
private:
	vector<int> C;
	
	void merge(int A[], int m, int B[], int n) {
		C.clear();
		
		int i, j;
		
		i = j = 0; // Bugged here, omitted this sentence
		while(i < m && j < n){
			if(A[i] <= B[j]){
				C.push_back(A[i++]);
			}else{
				C.push_back(B[j++]);
			}
		}
		
		while(i < m){
			C.push_back(A[i++]);
		}
		
		while(j < n){
			C.push_back(B[j++]);
		}
	}
};