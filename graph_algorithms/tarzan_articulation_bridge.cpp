#include <iostream>
#include <vector>

using namespace std;

void DfsUtil(int root, int parent, vector<vector<int>> &graph, vector<bool> &visited,
  vector<int> &discovery, vector<int> &low, vector<vector<int>> &result) {
      static int time = 0;
      discovery[root] = time;
      low[root] = time++;
      visited[root] = true;

      for (auto child : graph[root]) {
          if (!visited[child]) {
              DfsUtil(child, root, graph, visited, discovery, low, result);

              low[root] = min(low[root], low[child]);

              if (low[child] > discovery[root]) {
                  result.push_back({root, child});
              }
          } else if (child != parent) {
              low[root] = min(low[root], discovery[child]);
          }
      }

      return;
}

vector<vector<int>> GetArticulationBridges(vector<vector<int>> graph, int num_nodes) {
    vector<int> discovery(num_nodes), low(num_nodes);
    vector<bool> visited(num_nodes, false);
    vector<vector<int>> result;

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

    auto result = GetArticulationBridges(graph, 5);

    for (auto node : result) {
        cout << node[0] << " " << node[1] << endl;
    }
    return 0;
}