#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Solution {
public:
    Solution() {
        um[0] = "Zero";
        um[1] = "One";
        um[2] = "Two";
        um[3] = "Three";
        um[4] = "Four";
        um[5] = "Five";
        um[6] = "Six";
        um[7] = "Seven";
        um[8] = "Eight";
        um[9] = "Nine";
        um[10] = "Ten";
        um[11] = "Eleven";
        um[12] = "Twelve";
        um[13] = "Thirteen";
        um[14] = "Fourteen";
        um[15] = "Fifteen";
        um[16] = "Sixteen";
        um[17] = "Seventeen";
        um[18] = "Eighteen";
        um[19] = "Nineteen";
        um[20] = "Twenty";
        um[30] = "Thirty";
        um[40] = "Forty";
        um[50] = "Fifty";
        um[60] = "Sixty";
        um[70] = "Seventy";
        um[80] = "Eighty";
        um[90] = "Ninety";
        um[100] = "Hundred";
        um[1000] = "Thousand";
        um[1000000] = "Million";
        um[1000000000] = "Billion";
    }
    
    string numberToWords(int num) {
        vector<string> words;
        readNumber(num, words);
        ostringstream os;
        
        int i;
        os << words[0];
        for (i = 1; i < words.size(); ++i) {
            os << " " << words[i];
        }
        return os.str();
    }
protected:
    unordered_map<int, string> um;
    
    void readNumber(int val, vector<string> &words) {
        if (val == 0) {
            words.push_back(um[val]);
            return;
        }
        // Start from billion
        int base = 1000000000;
        while (base > 0) {
            if (val < base) {
                base /= 1000;
                continue;
            }
            readNumberWithin1000(val / base, words);
            if (base > 1) {
                words.push_back(um[base]);
            }
            
            val %= base;
            base /= 1000;
        }
    }
    
    void readNumberWithin1000(int val, vector<string> &v) {
        if (val >= 100) {
            v.push_back(um[val / 100]);
            v.push_back(um[100]);
            val %= 100;
        }
        if (val == 0) {
            return;
        }
        
        if (um.find(val) != um.end()) {
            v.push_back(um[val]);
        } else {
            v.push_back(um[val / 10 * 10]);
            v.push_back(um[val % 10]);
        }
    }
};