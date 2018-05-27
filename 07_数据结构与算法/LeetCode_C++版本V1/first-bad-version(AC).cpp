// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int low, high, mid;
        low = 1;
        if (isBadVersion(low)) {
            return low;
        }
        high = n;
        while (high - low > 1) {
            mid = low + (high - low) / 2;
            if (isBadVersion(mid)) {
                high = mid;
            } else {
                low = mid;
            }
        }
        return high;
    }
};