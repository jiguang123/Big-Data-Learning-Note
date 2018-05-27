class Solution {
public:
	int maxProfit(vector<int> &prices) {
		// Note: The Solution object is instantiated only once and is reused by each test case.
		int res;
		int i, len = prices.size();
		
		res = 0;
		for(i = 0; i < len - 1; ++i){
			if(prices[i] < prices[i + 1]){
				res += prices[i + 1] - prices[i];
			}
		}
		
		return res;
	}
};