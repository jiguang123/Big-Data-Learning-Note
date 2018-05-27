// 1RE, 1AC, solution using trie
class TrieNode {
public:
	bool is_word;
	
	TrieNode() {
		child = new TrieNode*[26];
		for (int i = 0; i < 26; ++i) {
			child[i] = NULL;
		}
		is_word = false;
	}
	
	~TrieNode() {
		delete[] child;
	}
	
	TrieNode **child;
};

class WordDictionary {
public:
	WordDictionary() {
		root = new TrieNode();
	}
	
	void addWord(string word) {
		int n = word.length();
		if (n == 0) {
			return;
		}
		
		TrieNode *p = root;
		for (int i = 0; i < n; ++i) {
			if (p->child[word[i] - 'a'] == NULL) {
				p->child[word[i] - 'a'] = new TrieNode();
			}
			p = p->child[word[i] - 'a'];
		}
		p->is_word = true;
	}

	bool search(string word) {
		return searchDFS(root, word, 0);
	}
private:
	TrieNode *root;
	
	bool searchDFS(TrieNode *p, const string &word, int idx) {
		if (p == NULL) {
			return false;
		}
		if (idx == word.length()) {
			return p->is_word;
		}
		if (word[idx] != '.') {
			return searchDFS(p->child[word[idx] - 'a'], word, idx + 1);
		}
		for (int i = 0; i < 26; ++i) {
			if (p->child[i] == NULL) {
				continue;
			}
			if (searchDFS(p->child[i], word, idx + 1)) {
				return true;
			}
		}
		return false;
	}
};
