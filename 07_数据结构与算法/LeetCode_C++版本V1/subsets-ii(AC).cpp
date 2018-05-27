// 1RE, 1AC, good~
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int i, j, n;
        
        n = result.size();
        for(i = 0; i < n; ++i){
            result[i].clear();
        }
        result.clear();
        
        sort(S.begin(), S.end());
        n = S.size();
        num.clear();
        count.clear();
        i = 0;
        while(i < n){
            j = i + 1;
            while(j < n && S[i] == S[j]){
                ++j;
            }
            num.push_back(S[i]);
            count.push_back(j - i);
            i = j;
        }
        n = num.size();
        arr.clear();
        dfs(0, n);
        
        return result;
    }
private:
    vector<int> num;
    vector<int> count;
    vector<vector<int>> result;
    vector<int> arr;
    
    void dfs(int idx, int n) {
        if(idx == n){
            result.push_back(arr);
            // 1RE here, stop $idx from going out of range.
            return;
        }
        
        int i, j;
        for(i = 0; i <= count[idx]; ++i){
            for(j = 0; j < i; ++j){
                arr.push_back(num[idx]);
            }
            dfs(idx + 1, n);
            for(j = 0; j < i; ++j){
                arr.pop_back();
            }
        }
    }
};