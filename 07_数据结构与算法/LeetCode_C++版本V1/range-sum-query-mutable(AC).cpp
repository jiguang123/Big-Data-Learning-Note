class NumArray {
public:
    NumArray(vector<int> &nums) {
        v.resize(nums.size() + 1, 0);
        n = nums.size();
        for (int i = 0; i < nums.size(); ++i) {
            add(i + 1, nums[i]);
        }
    }

    void update(int i, int newVal) {
        ++i;
        if (i < 1 || i > n) {
            return;
        }
        int oldVal = getSum(i) - getSum(i - 1);
        add(i, newVal - oldVal);
    }

    int sumRange(int i, int j) {
        return getSum(j + 1) - getSum(i);
    }
protected:
    vector<int> v;
    int n;
    
    void add(int idx, int val) {
        if (idx <= 0) {
            return;
        }
        int i = idx;
        while (i <= n) {
            v[i] += val;
            i += lowbit(i);
        }
    }
    
    int getSum(int idx) {
        int sum = 0;
        int i = idx;
        while (i > 0) {
            sum += v[i];
            i -= lowbit(i);
        }
        return sum;
    }
    
    int lowbit(int x) {
        return x & -x;
    }
};
