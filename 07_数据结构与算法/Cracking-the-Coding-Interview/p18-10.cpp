// 18.10 Given a list of words, all of same length. Given a source and a destionation words, you have to check if there exists a path between the two. Every time you may change only one letter in the word.
// This is my code from leetcode problem set: word ladder
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<string> > findLadders(string start, string end, unordered_set<string> &dict) {
		unordered_map<string, vector<string> > back_trace;
		vector<unordered_set<string> > level(2);
		
		dict.insert(start);
		dict.insert(end);
		
		int flag, nflag;
		flag = 0;
		nflag = !flag;
		level[flag].insert(start);
		
		unordered_set<string>::iterator usit;
		char ch, old_ch;
		string word;
		while (true) {
			flag = !flag;
			nflag = !nflag;
			level[flag].clear();
			for (usit = level[nflag].begin(); usit != level[nflag].end(); ++usit) {
				dict.erase(*usit);
			}
			for (usit = level[nflag].begin(); usit != level[nflag].end(); ++usit) {
				word = *usit;
				for (size_t i = 0; i < word.size(); ++i) {
					old_ch = word[i];
					for (ch = 'a'; ch <= 'z'; ++ch) {
						if (ch == old_ch) {
							continue;
						}
						word[i] = ch;
						if (dict.find(word) != dict.end()) {
							back_trace[word].push_back(*usit);
							level[flag].insert(word);
						}
					}
					word[i] = old_ch;
				}
			}
			if (level[flag].empty() || level[flag].count(end) > 0) {
				// found or not found
				break;
			}
		}
		
		single_result.clear();
		for (size_t i = 0; i < result.size(); ++i) {
			result[i].clear();
		}
		result.clear();
		
		if (!back_trace.empty()) {
			recorverPath(back_trace, end);
		}
		
		return result;
    }
private:
	vector<vector<string> > result;
	vector<string> single_result;
	
	void recorverPath(unordered_map<string, vector<string> > &back_trace, string cur) {
		if (back_trace.count(cur) == 0) {
			// this word has no back trace, it is unreachable.
			vector<string> single_path(single_result);
			
			single_path.push_back(cur);
			reverse(single_path.begin(), single_path.end());
			result.push_back(single_path);
			return;
		}
		
		const vector<string> &v = back_trace[cur];
		vector<string>::const_iterator usit;
		
		single_result.push_back(cur);
		for (usit = v.begin(); usit != v.end(); ++usit) {
			recorverPath(back_trace, *usit);
		}
		single_result.pop_back();
	}
};