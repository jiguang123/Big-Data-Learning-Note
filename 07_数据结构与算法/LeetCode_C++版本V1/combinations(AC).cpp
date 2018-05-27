// 1AC, very well
class Solution {
public:
    vector<vector<int> > combine(int n, int k) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int i;
        for(i = 0; i < result.size(); ++i){
            result[i].clear();
        }
        result.clear();
        
        if(n <= 0 || k <= 0){
            return result;
        }
        
        arr = new int[n];
        dfs(0, 0, n, k);
        delete[] arr;
        
        return result;
    }
private:
    vector<vector<int>> result;
    int *arr;
    
    void dfs(int idx, int cnt, int n, int k) {
        int i;
        
        if(cnt == k){
            result.push_back(vector<int>());
            for(i = 0; i < k; ++i){
                result[result.size() - 1].push_back(arr[i]);
            }
            return;
        }
        
        // trim redundant path to save some time
		if(idx + (k - cnt) > n){
			return;
		}
		
        for(i = idx; i < n; ++i){
            arr[cnt] = i + 1;
            dfs(i + 1, cnt + 1, n, k);
        }
    }
};