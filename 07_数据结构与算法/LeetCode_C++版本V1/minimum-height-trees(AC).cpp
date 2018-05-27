#include <algorithm>
#include <climits>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int> > &edges) {
        constructGraph(n, edges);
        
        dist.resize(n, INT_MAX);
        visited.resize(n, false);
        pre.resize(n, 0);
        
        // Start searching from arbitrary vertex and locate the furthest one
        int fv1 = BFS(0);
        // Start searching from the furthest vertex and locate the furthest one
        int fv2 = BFS(fv1);
        
        vector<int> path;
        int pl;
        int i = fv2;
        while (i != pre[i]) {
            path.push_back(i);
            i = pre[i];
        }
        path.push_back(i);
        pl = path.size();
        
        vector<int> ans;
        if (pl & 1) {
            ans.push_back(path[pl >> 1]);
        } else {
            ans.push_back(path[pl >> 1]);
            ans.push_back(path[(pl - 1) >> 1]);
        }
        
        dist.clear();
        pre.clear();
        visited.clear();
        graph.clear();
        
        return ans;
    }
protected:
    int n;
    vector<int> dist;
    vector<int> pre;
    vector<bool> visited;
    vector<unordered_set<int> > graph;
    
    int BFS(int start) {
        int i;
        for (i = 0; i < n; ++i) {
            dist[i] = INT_MAX;
            pre[i] = i;
            visited[i] = false;
        }
        queue<int> q;
        
        dist[start] = 0;
        pre[start] = start;
        visited[start] = true;
        q.push(start);
        
        int j;
        while (!q.empty()) {
            i = q.front();
            q.pop();
            for (auto it = graph[i].begin(); it != graph[i].end(); ++it) {
                j = *it;
                if (visited[j]) {
                    continue;
                }
                dist[j] = dist[i] + 1;
                pre[j] = i;
                visited[j] = true;
                q.push(j);
            }
        }
        
        int mdist = -1;
        int mi = 0;
        for (i = 0; i < n; ++i) {
            if (visited[i] && dist[i] > mdist) {
                mdist = dist[i];
                mi = i;
            }
        }
        return mi;
    }
    
    void constructGraph(int n, vector<pair<int, int> > &edges) {
        this->n = n;
        graph.resize(n);
        
        int m = edges.size();
        int i;
        for (i = 0; i < m; ++i) {
            graph[edges[i].first].insert(edges[i].second);
            graph[edges[i].second].insert(edges[i].first);
        }
    }
};
