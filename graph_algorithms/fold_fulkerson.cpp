// This is code for finding max flow in a directed graph using fold fulkerson method.
#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

class FoldFulkerson {
private:
    vector<vector<int>> _graph;
    int _numNodes;
public:
    FoldFulkerson(vector<vector<int>> &g) {
        _graph = g;
        _numNodes = g.size();
    }

    int getMaxFlow(int src, int dst) {
        int maxFlow = 0;

        vector<vector<int>> rGraph = vector<vector<int>>(_numNodes, vector<int>(_numNodes, 0));
        
        // initializing rgraph
        for (int i = 0; i < _numNodes; ++i) {
            for (int j = 0; j < _numNodes; ++j) {
                rGraph[i][j] = _graph[i][j];
            }
        }

        vector<int> parents;

        while(getAvailablePath(rGraph, src, dst, parents)) {
            int bottleNeck = INT_MAX;

            int parent = src;

            for (auto node : parents) {
                if (node == -1) break;
                bottleNeck = min(bottleNeck, rGraph[parent][node]);
                parent = node;
            }

            maxFlow += bottleNeck;

            parent = src;
            for (auto node : parents) {
                if (node == -1) break;
                rGraph[parent][node] -= bottleNeck;
                rGraph[node][parent] += bottleNeck;
                parent = node;
            }
            parents.clear();
        }
        return maxFlow;
    }
private:
    bool getAvailablePath(const vector<vector<int>> &graph, int src, int dst, vector<int> &parents) {
        vector<bool> visited = vector<bool>(_numNodes, false);
        return dfs(graph, src, dst, visited, parents);
    }
    
    bool dfs(const vector<vector<int>> &graph, int root, int dst, vector<bool> &visited, vector<int> &parents) {
        if (root == dst) return true;

        if (visited[root]) return false;

        visited[root] = true;

        for (int i = 0; i < graph.size(); ++i) {
            if (graph[root][i] != 0) {
                parents.push_back(i);
                if (dfs(graph, i, dst, visited, parents)) {
                    return true;
                }
                parents.pop_back();
            }
        }

        return false;
    }
};

int main() {
    // initialize graph
    vector<vector<int>> graph = {
        { 0, 16, 13, 0, 0, 0 },
        { 0, 0, 10, 12, 0, 0 },
        { 0, 4, 0, 0, 14, 0 },
        { 0, 0, 9, 0, 0, 20 },
        { 0, 0, 0, 7, 0, 4 },
        { 0, 0, 0, 0, 0, 0 }
    };

    FoldFulkerson foldFulkerson = FoldFulkerson(graph);
    cout << foldFulkerson.getMaxFlow(0, 5) << endl;
    return 0;
}