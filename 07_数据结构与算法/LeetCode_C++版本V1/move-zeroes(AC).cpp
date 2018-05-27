class Solution {
public:
    void moveZeroes(vector<int> &nums) {
        const int MOVE_VAL = 0;
        vector<int> &a = nums;
        int n = a.size();
        int i, j;
        i = j = 0;
        while (i < n) {
            if (a[i] != MOVE_VAL) {
                a[j++] = a[i++];
            } else {
                ++i;
            }
        }
        while (j < n) {
            a[j++] = MOVE_VAL;
        }
    }
};