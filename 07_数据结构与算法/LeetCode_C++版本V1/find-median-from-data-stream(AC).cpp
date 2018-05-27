#include <map>
using namespace std;

class MedianFinder {
public:
    MedianFinder() {
        bigSize = 0;
        smallSize = 0;
    }
    
    // Adds a number into the data structure.
    void addNum(int num) {
        if (bigSize == smallSize) {
            ++big[num];
            ++bigSize;
        } else {
            ++small[num];
            ++smallSize;
        }
        adjust();
    }

    // Returns the median of current data stream
    double findMedian() {
        if (bigSize == smallSize) {
            return (big.begin()->first + small.rbegin()->first) / 2.0;
        } else {
            return big.begin()->first;
        }
    }
private:
    map<int, int> big, small;
    int bigSize, smallSize;
    
    void adjust() {
        if (small.size() == 0) {
            return;
        }
        int b = big.begin()->first;
        int s = small.rbegin()->first;
        if (b >= s) {
            return;
        }
        remove(big, b);
        remove(small, s);
        ++big[s];
        ++small[b];
    }
    
    void remove(map<int, int> &m, int key) {
        auto it = m.find(key);
        if (it->second == 1) {
            m.erase(it);
        } else {
            --it->second;
        }
    }
};

// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();