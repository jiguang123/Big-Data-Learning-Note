// 13.7 Given a pointer to a Node strcut, return a deep copy of whatever you can find with it.
// Answer:
//	The following code is actually my solution to the leetcode problem, Clone Graph.
//	They are different problems, but almost the same idea of BFS, mapping and deep copy.
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;
/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
		if (node == nullptr) {
			return nullptr;
		}
		
		UndirectedGraphNode *cur, *nei;
		int i, j;
		int nc;
		int ix, iy;
		int nsize;
		
		nc = 0;
		qq.push(node);
		while (!qq.empty()) {
			cur = qq.front();
			qq.pop();
			if (um.find(cur) == um.end()) {
				um[cur] = nc++;
				graph.push_back(vector<int>());
				labels.push_back(cur->label);
				nodes_checked.push_back(false);
			}
			ix = um[cur];
			if (nodes_checked[ix]) {
				continue;
			}
			nsize = (int)cur->neighbors.size();
			for (i = 0; i < nsize; ++i) {
				nei = cur->neighbors[i];
				if (um.find(nei) == um.end()) {
					um[nei] = nc++;
					labels.push_back(nei->label);
					graph.push_back(vector<int>());
					nodes_checked.push_back(false);
				}
				iy = um[nei];
				if (!nodes_checked[iy]) {
					qq.push(nei);
				}
				graph[ix].push_back(iy);
			}
			nodes_checked[ix] = true;
		}
		
		new_nodes.clear();
		for (i = 0; i < nc; ++i) {
			new_nodes.push_back(new UndirectedGraphNode(labels[i]));
		}
		for (i = 0; i < nc; ++i) {
			nsize = (int)graph[i].size();
			for (j = 0; j < nsize; ++j) {
				new_nodes[i]->neighbors.push_back(new_nodes[graph[i][j]]);
			}
		}
		cur = new_nodes[0];
		while (!qq.empty()) {
			qq.pop();
		}
		um.clear();
		new_nodes.clear();
		for (i = 0; i < (int)graph.size(); ++i) {
			graph[i].clear();
		}
		graph.clear();
		labels.clear();
		nodes_checked.clear();
		
		return cur;
    }
private:
	queue<UndirectedGraphNode *> qq;
	unordered_map<UndirectedGraphNode *, int> um;
	vector<int> labels;
	vector<bool> nodes_checked;
	vector<UndirectedGraphNode *> new_nodes;
	vector<vector<int> > graph;
};