class Solution {
public:
    int maxProfit(vector<int> &prices) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int max_value;
		int max_profit;
		
		if(prices.size() <= 0){
			return 0;
		}
		
		int i, n;
		
		n = prices.size();
		for(i = n - 1; i >= 0; --i){
			if(i == n - 1){
				max_value = prices[i];
				max_profit = 0;
			}else{
				if(prices[i] > max_value){
					max_value = prices[i];
				}
				if(max_value - prices[i] > max_profit){
					max_profit = max_value - prices[i];
				}
			}
		}
		
		return max_profit;
    }
};