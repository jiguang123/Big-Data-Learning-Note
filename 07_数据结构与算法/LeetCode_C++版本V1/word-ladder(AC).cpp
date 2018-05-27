// 7CE, 4RE, 4TLE, 1AC, BFS...
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
	int ladderLength(string start, string end, unordered_set<string> &dict) {
		queue<pair<string, int> > qq;
		string word, next_word;
		unordered_map<string, int> um;
		char ch, old_ch;
		int result = 0;
		bool suc = false;
		pair<string, int> this_pair;
		
		qq.push(make_pair(start, 1));
		um[start] = 1;
		while (!qq.empty()) {
			this_pair = qq.front();
			qq.pop();
			word = this_pair.first;
			for (size_t i = 0; i < word.length(); ++i) {
				old_ch = word[i];
				for (ch = 'a'; ch <= 'z'; ++ch) {
					word[i] = ch;
					if (word == end) {
						suc = true;
						result = this_pair.second + 1;
					}
					if (um.find(word) == um.end() && dict.find(word) != dict.end()) {
						qq.push(make_pair(word, this_pair.second + 1));
						um[word] = this_pair.second + 1;
					}
				}
				if (suc) {
					break;
				}
				word[i] = old_ch;
			}
			if (suc) {
				break;
			}
		}
		while(!qq.empty()) {
			qq.pop();
		}
		return result;
	}
};