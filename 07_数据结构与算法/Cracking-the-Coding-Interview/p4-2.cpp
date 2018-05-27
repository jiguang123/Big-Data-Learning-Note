// 4.2 Write a program to check if there exists a path between two nodes in a directed graph.
#include <algorithm>
#include <cstdio>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

struct  GraphNode {
	int label;
	unordered_set<GraphNode *> neighbors;
	
	GraphNode(int _label = 0): label(_label) {};
};

bool hasPath(GraphNode *n1, GraphNode *n2, unordered_set<GraphNode *> &checked, vector<GraphNode *> &path)
{
	if (n1 == nullptr || n2 == nullptr) {
		return false;
	}
	
	checked.insert(n1);
	path.push_back(n1);

	if (n1 == n2) {
		return true;
	}

	unordered_set<GraphNode *>::iterator it;
	for (it = n1->neighbors.begin(); it != n1->neighbors.end(); ++it) {
		if (checked.find(*it) == checked.end()) {
			if (hasPath(*it, n2, checked, path)) {
				return true;
			}
		}
	}
	checked.erase(n1);
	path.pop_back();
	return false;
}

void constructGraph(int n, vector<GraphNode *> &nodes)
{
	int i;
	int ne, x, y;
	int label;
	
	nodes.resize(n);
	for (i = 0; i < n; ++i) {
		scanf("%d", &label);
		nodes[i] = new GraphNode(label);
	}
	
	scanf("%d", &ne);
	for (i = 0; i < ne; ++i) {
		scanf("%d%d", &x, &y);
		nodes[x]->neighbors.insert(nodes[y]);
	}
}

void clearGraph(vector<GraphNode *> &nodes)
{
	int n = (int)nodes.size();
	int i;
	
	for (i = 0; i < n; ++i) {
		nodes[i]->neighbors.clear();
		delete nodes[i];
		nodes[i] = nullptr;
	}
	nodes.clear();
}

int main()
{
	int n;
	vector<GraphNode *> nodes;
	vector<GraphNode *> path;
	unordered_set<GraphNode *> checked;
	int idx1, idx2;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		constructGraph(n, nodes);
		while (scanf("%d%d", &idx1, &idx2) == 2 && (idx1 >= 0 && idx2 >= 0)) {
			if (idx1 >= n || idx2 >= n) {
				continue;
			}

			if (hasPath(nodes[idx1], nodes[idx2], checked, path)) {
				printf("Yes\n");
				printf("%d", path[0]->label);
				for (int i = 1; i < (int)path.size(); ++i) {
					printf("->%d", path[i]->label);
				}
				printf("\n");
			} else {
				printf("No\n");
			}
			checked.clear();
			path.clear();
		}
		clearGraph(nodes);
	}
	
	return 0;
}