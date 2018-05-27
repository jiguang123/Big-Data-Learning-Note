// 2CE, 1RE, 1AC
// Such a problem is not about algorithm, it is about being bug-free.
// So, be sure to read your code before submitting.
// It is guaranteed that all words contain only lower-case letters.
class TrieNode {
public:
	static const int N = 26;
	bool is_word;
	
    // Initialize your data structure here.
    TrieNode() {
		// typing error here
		// child = new TrieNode[N];
		child = new TrieNode*[N];
		for (int i = 0; i < N; ++i) {
			// typing error here.
			// child[N] = NULL;
			child[i] = NULL;
		}
		is_word = false;
    }
	
	~TrieNode() {
		delete[] child;
	}
	
	TrieNode **child;
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word) {
		int n = word.length();
		
		if (n == 0) {
			return;
		}
		
		TrieNode *p1;
		
		p1 = root;
		for (int i = 0; i < n; ++i) {
			if (p1->child[word[i] - 'a'] == NULL) {
				p1->child[word[i] - 'a'] = new TrieNode();
			}
			p1 = p1->child[word[i] - 'a'];
		}
		p1->is_word = true;
    }

    // Returns if the word is in the trie.
    bool search(string word) {
		int n = word.length();
		
		if (n == 0) {
			return false;
		}
		
		TrieNode *p1;
		
		p1 = root;
		for (int i = 0; i < n; ++i) {
			if (p1->child[word[i] - 'a'] == NULL) {
				return false;
			}
			p1 = p1->child[word[i] - 'a'];
		}
		return p1->is_word;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
		// typing error here
		// int n = word.length();
		int n = prefix.length();
		
		if (n == 0) {
			return true;
		}
		
		TrieNode *p1;
		
		p1 = root;
		for (int i = 0; i < n; ++i) {
			if (p1->child[prefix[i] - 'a'] == NULL) {
				return false;
			}
			p1 = p1->child[prefix[i] - 'a'];
		}
		return p1 != NULL;
    }

private:
    TrieNode* root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");