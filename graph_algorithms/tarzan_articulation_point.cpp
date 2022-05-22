#include <iostream>
#include <vector>

using namespace std;

void DfsUtil(int root, int parent, vector<vector<int>> &graph, vector<bool> &visited,
  vector<int> &discovery, vector<int> &low, vector<int> &result) {
      static int time = 0;
      discovery[root] = time;
      low[root] = time++;
      visited[root] = true;

      int children = 0;
      bool is_ap = false;

      for (auto child : graph[root]) {
          if (!visited[child]) {
              ++children;
              DfsUtil(child, root, graph, visited, discovery, low, result);

              low[root] = min(low[root], low[child]);

              if (low[child] >= discovery[root]) {
                  is_ap = true;
              }
          } else if (child != parent) {
              low[root] = min(low[root], discovery[child]);
          }
      }

      if (parent == -1 && children > 1) {
          is_ap = true;
      }

      if (is_ap) result.push_back(root);
      return;
}

vector<int> GetArticulationPoints(vector<vector<int>> graph, int num_nodes) {
    vector<int> discovery(num_nodes), low(num_nodes);
    vector<bool> visited(num_nodes, false);
    vector<int> result;

    for (int i = 0; i < num_nodes; ++i) {
        if (!visited[i]) {
            DfsUtil(i, -1, graph, visited, discovery, low, result);
        }
    }
    return result;
}

int main() {
    vector<vector<int>> graph(5, vector<int>());
    vector<vector<int>> edges {{1,0},{0,2},{2,1},{0,3},{3,4}};

    for (auto edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
    }

    auto result = GetArticulationPoints(graph, 5);

    for (auto node : result) {
        cout << node << " ";
    }
    cout << endl;
    return 0;
}