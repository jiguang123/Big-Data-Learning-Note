// 1WA, 1AC, O(n) online solution.
class Solution {
public:
	int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
		int total_sum;
		int current_sum;
		int i;
		int n;
		int start_pos;
		
		n = (int)gas.size();
		if (n == 0) {
			return -1;
		}
		
		total_sum = current_sum = 0;
		start_pos = 0;
		for (i = 0; i < n; ++i) {
			total_sum += gas[i] - cost[i];
			current_sum += gas[i] - cost[i];
			if (current_sum < 0) {
				// you cannot finish the trip
				// because you used us the gasoline here
				// need a new start from next station
				start_pos = (i + 1) % n;
				current_sum = 0;
			}
		}
		
		if (total_sum < 0) {
			// impossible to finish the trip
			return -1;
		} else {
			return start_pos;
		}
	}
};