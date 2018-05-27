// 1CE, 2MLE, 1AC, not so easy
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int> &num) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int i, j;
        int n;
        
        n = result.size();
        for(i = 0; i < n; ++i){
            result[i].clear();
        }
        result.clear();
        
        sort(num.begin(), num.end());
        n = num.size();
        if(n <= 0){
            return result;
        }
        while(true){
            result.push_back(num);
            for(i = n - 1; i > 0; --i){
                if(num[i - 1] < num[i]){
                    break;
                }
            }
            if(i <= 0){
                break;
            }
            --i;
            for(j = n - 1; j > i; --j){
                if(num[j] > num[i]){
                    break;
                }
            }
            myswap(num[j], num[i]);
            // 2MLE here, reverse(i + 1, n - 1), not reverse(i, n - 1);
            reverse(num, i + 1, n - 1);
        }
        
        return result;
    }
private:
    vector<vector<int>> result;
    void myswap(int &x, int &y) {
        int tmp;
        
        tmp = x;
        x = y;
        y = tmp;
    }
    
    void reverse(vector<int> &num, int left, int right) {
        int i;
        
        if(left > right){
            reverse(num, right, left);
            return;
        }
        
        i = left;
        // 1CE here, how did you submit before even finishing it!!!
        while(i < left + right - i){
            myswap(num[i], num[left + right - i]);
            ++i;
        }
    }
};