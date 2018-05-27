// 3CE, 1RE, 1WA, 1AC, trial and error.
static int N = 26;

class TrieNode {
public:
	bool is_word;
	TrieNode **child;
	
    TrieNode() {
		child = new TrieNode*[N];
		for (int i = 0; i < N; ++i) {
			child[i] = NULL;
		}
		is_word = false;
    }
	
	~TrieNode() {
		delete[] child;
	}
};

class Solution {
public:
	Solution () {
		d[0][0] = -1;
		d[0][1] = 0;
		d[1][0] = +1;
		d[1][1] = 0;
		d[2][0] = 0;
		d[2][1] = -1;
		d[3][0] = 0;
		d[3][1] = +1;
	}
	
    vector<string> findWords(vector<vector<char> >& board, vector<string>& words) {
		ans.clear();
		n = board.size();
		if (n == 0) {
			return ans;
		}
		m = board[0].size();
		if (m == 0) {
			return ans;
		}
		
		root = new TrieNode();
		int i;
		for (i = 0; i < words.size(); ++i) {
			insert(words[i]);
		}
		
		int j;
		string w = "";
		b.resize(n, vector<bool>(m, false));
		for (i = 0; i < n; ++i) {
			for (j = 0; j < m; ++j) {
				DFS(w, i, j, root, board);
			}
		}
		
		unordered_set<string>::iterator it;
		for (it = us.begin(); it != us.end(); ++it) {
			ans.push_back(*it);
		}
		clearUp(root);
		us.clear();
		
		return ans;
    }
private:
    TrieNode* root;
	int d[4][2];
	vector<string> ans;
	unordered_set<string> us;
	vector<vector<bool> > b;
	int n, m;
	
	bool inbound(int x, int y) {
		return x >= 0 && x <= n - 1 && y >= 0 && y <= m - 1;
	}
	
	void DFS(string &w, int x, int y, TrieNode *p, vector<vector<char> > &a) {
		TrieNode *p1 = p->child[a[x][y] - 'a'];
		if (p1 == NULL) {
			return;
		}
		w.push_back(a[x][y]);
		b[x][y] = true;
		
		if (p1->is_word) {
			// A word is found.
			us.insert(w);
		}
		
		int x1, y1;
		int i;
		for (i = 0; i < 4; ++i) {
			x1 = x + d[i][0];
			y1 = y + d[i][1];
			if (!inbound(x1, y1) || b[x1][y1]) {
				continue;
			}
			DFS(w, x1, y1, p1, a);
		}
		
		b[x][y] = false;
		w.pop_back();
	}
	
    void insert(string word) {
		int n = word.length();
		
		if (n == 0) {
			return;
		}
		
		TrieNode *p;
		
		p = root;
		for (int i = 0; i < n; ++i) {
			if (p->child[word[i] - 'a'] == NULL) {
				p->child[word[i] - 'a'] = new TrieNode();
			}
			p = p->child[word[i] - 'a'];
		}
		p->is_word = true;
    }
	
	void clearUp(TrieNode *&r) {
		if (r == NULL) {
			return;
		}
		
		int i;
		for (i = 0; i < N; ++i) {
			clearUp(r->child[i]);
		}
		delete r;
		r = NULL;
	}
};