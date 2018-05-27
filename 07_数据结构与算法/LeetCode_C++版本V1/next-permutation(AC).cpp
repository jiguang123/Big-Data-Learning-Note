// 1WA, 1AC
class Solution {
public:
    void nextPermutation(vector<int> &num) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int i, j, n;
        int tmp;
        
        n = num.size();
        // 1WA here, wrong direction of $i
        i = n - 2;
        while(i >= 0 && num[i] >= num[i + 1]){
            --i;
        }
        
        if(i == -1){
            reverse(num, 0, n - 1);
            return;
        }
        
        j = n - 1;
        while(num[i] >= num[j]){
            --j;
        }
        tmp = num[i];
        num[i] = num[j];
        num[j] = tmp;
        
        reverse(num, i + 1, n - 1);
    }
private:
    void reverse(vector<int> &num, int left, int right) {
        int tmp;
        int i;
        
        if(left >= right){
            return;
        }
        
        i = left;
        while(i < left + right - i){
            tmp = num[i];
            num[i] = num[left + right - i];
            num[left + right - i] = tmp;
            ++i;
        }
    }
};