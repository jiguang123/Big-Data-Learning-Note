// 1WA, 1AC, standard Brute-Force solution.
#include <cstring>
using namespace std;

class Solution {
public:
    char *strStr(char *haystack, char *needle) {
        const char *ptr = haystack;
        size_t len = strlen(needle);
        if (len == 0) {
            return haystack;
        }
        while ((ptr = strchr(ptr, *needle)) != nullptr) {
            if (strncmp(ptr, needle, len) == 0) {
                return (char *)ptr;
            }
            ++ptr;
        }
    }
};