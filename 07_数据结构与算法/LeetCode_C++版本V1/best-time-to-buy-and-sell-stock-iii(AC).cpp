// 1RE, 1WA, 1AC, good
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        
        // 1RE here, didn't take empty array into account
        if(prices.size() <= 0){
            return 0;
        }
        
        int *a1, *a2;
        int n;
        int i, mv;
        
        n = prices.size();
        a1 = new int[n];
        a2 = new int[n];
        
        a1[0] = 0;
        mv = prices[0];
        for(i = 1; i < n; ++i){
            if(prices[i] < mv){
                mv = prices[i];
            }
            // 1WA here, prices[i] not a1[i]
            a1[i] = prices[i] - mv > a1[i - 1] ? prices[i] - mv : a1[i - 1];
        }
        
        a2[n - 1] = 0;
        mv = prices[n - 1];
        for(i = n - 2; i >= 0; --i){
            if(prices[i] > mv){
                mv = prices[i];
            }
            a2[i] = mv - prices[i] > a2[i + 1] ? mv - prices[i] : a2[i + 1];
        }
        
        mv = a1[0];
        for(i = 1; i < n; ++i){
            if(a1[i] > mv){
                mv = a1[i];
            }
        }
        
        for(i = 0; i < n; ++i){
            if(a2[i] > mv){
                mv = a2[i];
            }
        }
        
        for(i = 0; i < n - 1; ++i){
            if(a1[i] + a2[i + 1] > mv){
                mv = a1[i] + a2[i + 1];
            }
        }
        
        delete[] a1;
        delete[] a2;
        a1 = nullptr;
        a2 = nullptr;
        
        return mv;
    }
};