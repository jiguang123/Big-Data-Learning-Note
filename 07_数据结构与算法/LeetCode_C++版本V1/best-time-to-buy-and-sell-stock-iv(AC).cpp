// Yet to grasp the mechanism here... DP wasn't easy.
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(int k, vector<int> &prices) {
		int n = prices.size();
		
		if (k >= n) {
		    return easyMaxProfit(prices);
		}
		
		int i, j;
		vector<int> local, global;
		
		local.resize(n + 1, 0);
		global.resize(n + 1, 0);
		int diff;
		for (i = 1; i < n; ++i) {
			diff = prices[i] - prices[i - 1];
			for (j = k; j >= 1; --j) {
				local[j] = max(global[j - 1] + max(diff, 0), local[j] + diff);
				global[j] = max(global[j], local[j]);
			}
		}
		return global[k];
    }
private:
	int easyMaxProfit(vector<int> &prices) {
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