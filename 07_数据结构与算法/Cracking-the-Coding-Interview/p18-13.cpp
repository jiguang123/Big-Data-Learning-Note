// 18.13 There is a matrix of lower case letters. Given a dictionary of words, you have to find the maximum subrectangle, such that every row reading from left to right, and every column reading from top to bottom is a word in the dictionary. Return the area as the result.
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

const int MAX_NODE = 10000;

struct TrieNode {
	bool is_word;
	char ch;
	vector<int> child;
	TrieNode(char _ch = 0): is_word(false), ch(_ch), child(vector<int>(26, -1)) {};
};
int node_count;
TrieNode nodes[MAX_NODE];

void insertWordIntoTrie(int root, const string &s)
{
	int len = s.length();
	
	for (int i = 0; i < len; ++i) {
		if (nodes[root].child[s[i] - 'a'] < 0) {
			nodes[root].child[s[i] - 'a'] = node_count++;
			root = nodes[root].child[s[i] - 'a'];
			nodes[root].ch = s[i];
		} else {
			root = nodes[root].child[s[i] - 'a'];
		}
		if (i == len - 1) {
			nodes[root].is_word = true;
		}
	}
}

int constructTrie(const unordered_set<string> &dict)
{
	int root = node_count++;
	
	unordered_set<string>::const_iterator usit;
	for (usit = dict.begin(); usit != dict.end(); ++usit) {
		insertWordIntoTrie(root, *usit);
	}
	
	return root;
}

int main()
{
	int i, j, k;
	int i1, i2;
	string s;
	int n, m;
	vector<vector<char> > matrix;
	vector<vector<vector<bool> > > is_row_word;
	vector<vector<vector<bool> > > is_col_word;
	vector<int> dp;
	unordered_set<string> dict;
	int root;
	int ptr;
	int max_area;
	
	while (cin >> n && n > 0) {
		node_count = 0;
		for (i = 0; i < n; ++i) {
			cin >> s;
			dict.insert(s);
		}
		root = constructTrie(dict);
		
		cin >> n >> m;
		
		matrix.resize(n);
		for (i = 0; i < n; ++i) {
			matrix[i].resize(m);
		}
		for (i = 0; i < n; ++i) {
			cin >> s;
			for (j = 0; j < m; ++j) {
				matrix[i][j] = s[j];
			}
		}
		
		is_row_word.resize(n);
		for (i = 0; i < n; ++i) {
			is_row_word[i].resize(m);
			for (j = 0; j < m; ++j) {
				is_row_word[i][j].resize(m);
			}
		}

		is_col_word.resize(m);
		for (i = 0; i < m; ++i) {
			is_col_word[i].resize(n);
			for (j = 0; j < n; ++j) {
				is_col_word[i][j].resize(n);
			}
		}
		
		for (i = 0; i < n; ++i) {
			for (j = 0; j < m; ++j) {
				ptr = root;
				for (k = j; k < m; ++k) {
					if (ptr < 0) {
						is_row_word[i][j][k] = false;
						continue;
					}
					
					ptr = nodes[ptr].child[matrix[i][k] - 'a'];
					if (ptr < 0) {
						is_row_word[i][j][k] = false;
						continue;
					}
					
					is_row_word[i][j][k] = nodes[ptr].is_word;
				}
			}
		}
		
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j) {
				ptr = root;
				for (k = j; k < n; ++k) {
					if (ptr < 0) {
						is_col_word[i][j][k] = false;
						continue;
					}
					
					ptr = nodes[ptr].child[matrix[k][i] - 'a'];
					if (ptr < 0) {
						is_col_word[i][j][k] = false;
						continue;
					}
					
					is_col_word[i][j][k] = nodes[ptr].is_word;
				}
			}
		}
		
		max_area = 0;
		dp.resize(m);
		for (i1 = 0; i1 < n; ++i1) {
			for (i2 = i1; i2 < n; ++i2) {
				k = 0;
				for (j = 0; j < m; ++j) {
					dp[j] = is_col_word[j][i1][i2] ? (++k) : (k = 0);
					if (!dp[j]) {
						continue;
					}
					
					for (i = i1; i <= i2; ++i) {
						if (!is_row_word[i][j - dp[j] + 1][j]) {
							break;
						}
					}
					if (i > i2) {
						max_area = max(max_area, (i2 - i1 + 1) * dp[j]);
					}
				}
			}
		}
		
		cout << max_area << endl;
		
		// clear up data
		dict.clear();
		for (i = 0; i < n; ++i) {
			matrix[i].clear();
		}
		matrix.clear();
		
		for (i = 0; i < n; ++i) {
			for (j = 0; j < m; ++j) {
				is_row_word[i][j].clear();
			}
			is_row_word[i].clear();
		}
		is_row_word.clear();
		
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j) {
				is_col_word[i][j].clear();
			}
			is_col_word[i].clear();
		}
		is_col_word.clear();
	}
	
	return 0;
}