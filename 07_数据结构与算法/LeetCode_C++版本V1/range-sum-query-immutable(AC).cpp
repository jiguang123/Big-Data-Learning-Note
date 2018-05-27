#include <vector>
using namespace std;

class NumArray {
public:
    NumArray(vector<int> &nums) {
        n = nums.size();
        int s = 0;
        for (int i = 0; i < n; ++i) {
            sum.push_back(s += nums[i]);
        }
    }

    int sumRange(int i, int j) {
        return i > 0 ? sum[j] - sum[i - 1] : sum[j];
    }
protected:
    vector<int> sum;
    int n;
};
// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.sumRange(1, 2);