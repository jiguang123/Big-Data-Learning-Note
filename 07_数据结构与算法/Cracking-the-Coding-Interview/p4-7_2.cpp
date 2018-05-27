// 4.7 Least Common Ancestor
// O(log(n)) solution with binary decomposition.
#include <cstdio>
#include <cstring>
using namespace std;

typedef struct st{
public:
	int key;
	st *ll;
	st *rr;
	st(int _key = 0): key(_key), ll(NULL), rr(NULL) {}
}st;

// maximal number of nodes
const int MAXN = 10005;
// key -> node_index mapping
int hash_key[MAXN];
// node_index -> key mapping
int key_hash[MAXN];
// depth of each node
int depth[MAXN];
// array recording ancestors
int anc[MAXN][16];
// total number of nodes, index starting from 1
int nc;

// recursively calculate depths of nodes
void getDepth(st *root, int dep)
{
	if (root == NULL) {
		return;
	}
	depth[hash_key[root->key]] = dep;
	if (root->ll != NULL) {
		getDepth(root->ll, dep + 1);
	}
	if (root->rr != NULL) {
		getDepth(root->rr, dep + 1);
	}
}

// recursively construct a binary tree
void constructBinaryTree(st *&root)
{
	int tmp;

	scanf("%d", &tmp);
	if (tmp == 0) {
		root = NULL;
	} else {
		root = new st(tmp);
		++nc;
		if (hash_key[tmp] == 0) {
			hash_key[tmp] = nc;
		}
		key_hash[nc] = tmp;
		constructBinaryTree(root->ll);
		constructBinaryTree(root->rr);
	}
}

// recursively initialize ancestor array
void getParent(st *root)
{
	if (root == NULL) {
		return;
	}

	// anc[x][0] is the direct parent of x.
	if (root->ll != NULL) {
		anc[hash_key[root->ll->key]][0] = hash_key[root->key];
		getParent(root->ll);
	}
	if (root->rr != NULL) {
		anc[hash_key[root->rr->key]][0] = hash_key[root->key];
		getParent(root->rr);
	}
}

// calculate LCA in O(log(n)) time
int leastCommonAncestor(int x, int y)
{
	int i;

	if (depth[x] < depth[y]) {
		return leastCommonAncestor(y, x);
	}
	for (i = 15; i >= 0; --i) {
		if (depth[anc[x][i]] >= depth[y]) {
			x = anc[x][i];
			if (depth[x] == depth[y]) {
				break;
			}
		}
	}
	if (x == y) {
		return x;
	}

	for (i = 15; i >= 0; --i) {
		if (anc[x][i] != anc[y][i]) {
			// they'll finally be equal, think about the reason.
			x = anc[x][i];
			y = anc[y][i];
		}
	}

	// this is the direct parent of x
	return anc[x][0];
}

st *deleteTree(st *root)
{
	if (NULL == root) {
		return NULL;
	}

	if (root->ll != NULL) {
		root->ll = deleteTree(root->ll);
	}
	if (root->rr != NULL) {
		root->rr = deleteTree(root->rr);
	}
	delete root;
	root = NULL;

	return NULL;
}

int main()
{
	int ci, cc;
	int i, j;
	int x, y;
	st *root;

	while (scanf("%d", &cc) == 1) {
		for (ci = 0; ci < cc; ++ci) {
			// data initialization 
			memset(hash_key, 0, MAXN * sizeof(int));
			memset(key_hash, 0, MAXN * sizeof(int));
			memset(depth, 0, MAXN * sizeof(int));
			memset(anc, 0, MAXN * 16 * sizeof(int));
			nc = 0;
			root = NULL;

			constructBinaryTree(root);
			getParent(root);
			getDepth(root, 1);
			for (j = 1; j < 16; ++j) {
				for (i = 1; i <= nc; ++i) {
					anc[i][j] = anc[anc[i][j - 1]][j - 1];
				}
			}
			while (scanf("%d%d", &x, &y) == 2 && (x && y)) {
				if (hash_key[x] == 0 || hash_key[y] == 0) {
					printf("Not found in the tree.\n");
				} else {
					printf("%d\n", key_hash[leastCommonAncestor(hash_key[x], hash_key[y])]);
				}
			}

			root = deleteTree(root);
		}
	}

	return 0;
}