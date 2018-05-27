// 4.7 Least Common Ancestor
// Tarjan Offline Algorithm
#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	
	TreeNode(int _val = 0): val(_val), left(nullptr), right(nullptr) {};
};

void constructTree(vector<TreeNode *> &nodes, 
				   unordered_set<TreeNode *> &checked)
{
	int ll, rr;
	int i;

	for (i = 0; i < (int)nodes.size(); ++i) {
		checked.insert(nodes[i]);
	}
	for (i = 0; i < (int)nodes.size(); ++i) {
		scanf("%d%d", &ll, &rr);
		if (ll > 0) {
			nodes[i]->left = nodes[ll - 1];
			checked.erase(nodes[ll - 1]);
		}
		if (rr > 0) {
			nodes[i]->right = nodes[rr - 1];
			checked.erase(nodes[rr - 1]);
		}
	}
}

TreeNode *findRoot(TreeNode *node, unordered_map<TreeNode *, TreeNode *> &disjoint_set)
{
	if (node != disjoint_set[node]) {
		disjoint_set[node] = findRoot(disjoint_set[node], disjoint_set);
	}
	
	return disjoint_set[node];
}

void tarjanLCA(TreeNode *root, unordered_map<TreeNode *, TreeNode *> &disjoint_set, 
			   unordered_map<TreeNode *, unordered_map<TreeNode *, TreeNode *> > &query, 
			   unordered_set<TreeNode *> &checked)
{
	if (root == nullptr) {
		return;
	}
	
	disjoint_set[root] = root;
	if (root->left != nullptr) {
		tarjanLCA(root->left, disjoint_set, query, checked);
		disjoint_set[root->left] = root;
	}
	if (root->right != nullptr) {
		tarjanLCA(root->right, disjoint_set, query, checked);
		disjoint_set[root->right] = root;
	}
	checked.insert(root);
	
	if (query.find(root) == query.end()) {
		return;
	}
	
	unordered_map<TreeNode *, TreeNode *>::iterator it;
	for (it = query[root].begin(); it != query[root].end(); ++it) {
		if (it->second != nullptr) {
			// already solved, skip it
			continue;
		}
		if (checked.find(it->first) != checked.end()) {
			query[root][it->first] = query[it->first][root] = findRoot(it->first, disjoint_set);
		}
	}
}

int main()
{
	int n;
	int i;
	int val;
	vector<TreeNode *> nodes;
	TreeNode *root;
	unordered_map<TreeNode *, TreeNode *> disjoint_set;
	unordered_map<TreeNode *, unordered_map<TreeNode *, TreeNode *> > query;
	unordered_map<TreeNode *, unordered_map<TreeNode *, TreeNode *> >::iterator it1;
	unordered_set<TreeNode *> checked;
	unordered_map<TreeNode *, TreeNode *>::iterator it2;
	int idx1, idx2;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		nodes.resize(n);
		for (i = 0; i < n; ++i) {
			scanf("%d", &val);
			nodes[i] = new TreeNode(val);
		}
		constructTree(nodes, checked);
		root = *(checked.begin());
		checked.clear();
		
		while (scanf("%d%d", &idx1, &idx2) == 2 && (idx1 >= 0 && idx2 >= 0)) {
			if (idx1 > idx2) {
				i = idx1;
				idx1 = idx2;
				idx2 = i;
			}
			query[nodes[idx1]][nodes[idx2]] = nullptr;
			query[nodes[idx2]][nodes[idx1]] = nullptr;
		}
		// Tarjan Offline Algorithm
		tarjanLCA(root, disjoint_set, query, checked);
		
		// print the results
		for (it1 = query.begin(); it1 != query.end(); ++it1) {
			for (it2 = (it1->second).begin(); it2 != (it1->second).end(); ++it2) {
				if (it1->first->val > it2->first->val) {
					continue;
				}
				printf("The least common ancestor of %d and %d is %d.\n", 
					   it1->first->val, it2->first->val, it2->second->val);
			}
		}
		
		// clear up
		disjoint_set.clear();
		checked.clear();
		for (it1 = query.begin(); it1 != query.end(); ++it1) {
			(it1->second).clear();
		}
		query.clear();
	}
	
	return 0;
}