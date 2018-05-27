// 4.9 Find all paths in a binary tree, the path doesn't have to start or end at the root or a leaf node.
#include <cstdio>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	
	TreeNode(int _val = 0):val(_val), left(nullptr), right(nullptr) {};
};

void constructTree(TreeNode *&root)
{
	int val;
	
	scanf("%d", &val);
	if (val == 0) {
		root = nullptr;
	} else {
		root = new TreeNode(val);
		constructTree(root->left);
		constructTree(root->right);
	}
}

void constructGraph(TreeNode *root, unordered_map<TreeNode *, unordered_set<TreeNode *> > &graph)
{
	if (root->left != nullptr) {
		graph[root].insert(root->left);
		graph[root->left].insert(root);
		constructGraph(root->left, graph);
	}
	
	if (root->right != nullptr) {
		graph[root].insert(root->right);
		graph[root->right].insert(root);
		constructGraph(root->right, graph);
	}
}

void DFS(TreeNode *node, vector<TreeNode *> &path, int sum, const int target, 
		 unordered_set<TreeNode *> &checked, 
		 unordered_map<TreeNode *, unordered_set<TreeNode *> > &graph, vector<vector<TreeNode *> > &result)
{
	path.push_back(node);
	checked.insert(node);
	
	if (sum == target) {
		result.push_back(path);
	}
	unordered_set<TreeNode *>::iterator it;
	for (it = graph[node].begin(); it != graph[node].end(); ++it) {
		if (checked.find(*it) == checked.end()) {
			DFS(*it, path, sum + (*it)->val, target, checked, graph, result);
		}
	}
	
	checked.erase(node);
	path.pop_back();
}

void doDFS(TreeNode *root, vector<TreeNode *> &path, const int target, 
		 unordered_set<TreeNode *> &checked, 
		 unordered_map<TreeNode *, unordered_set<TreeNode *> > &graph, vector<vector<TreeNode *> > &result)
{
	path.clear();
	checked.clear();
	DFS(root, path, root->val, target, checked, graph, result);
	if (root->left != nullptr) {
		doDFS(root->left, path, target, checked, graph, result);
	}
	if (root->right != nullptr) {
		doDFS(root->right, path, target, checked, graph, result);
	}
}

void clearTree(TreeNode *&root)
{
	if (root == nullptr) {
		return;
	}
	
	if (root->left != nullptr) {
		clearTree(root->left);
	}
	if (root->right != nullptr) {
		clearTree(root->right);
	}
	delete root;
	root = nullptr;
}

int main()
{
	int i, j;
	int target;
	TreeNode *root;
	unordered_map<TreeNode *, unordered_set<TreeNode *> > graph;
	unordered_map<TreeNode *, unordered_set<TreeNode *> >::iterator it;
	unordered_set<TreeNode *> checked;
	vector<TreeNode *> path;
	vector<vector<TreeNode *> > result;
	
	while (true) {
		constructTree(root);
		if (root == nullptr) {
			break;
		}
		constructGraph(root, graph);
		while (scanf("%d", &target) == 1 && target) {
			doDFS(root, path, target, checked, graph, result);
			if (result.empty()) {
				printf("No path is found.\n");
			} else {
				for (i = 0; i < (int)result.size(); ++i) {
					printf("%d", result[i][0]->val);
					for (j = 1; j < (int)result[i].size(); ++j) {
						printf("->%d", result[i][j]->val);
					}
					result[i].clear();
					printf("\n");
				}
				result.clear();
			}
			path.clear();
			checked.clear();
		}
		for (it = graph.begin(); it != graph.end(); ++it) {
			(it->second).clear();
		}
		graph.clear();
		clearTree(root);
	}
	
	return 0;
}