#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;


struct Edge {
    string src;
    string dst;
    int weight;
};

map<string, int> bellman_ford(vector<Edge> edges, string source) {
    int num_nodes;
    map<string, int> distances;

    for (auto edge : edges) {
        distances[edge.src] = INT_MAX;
        distances[edge.dst] = INT_MAX;
    }

    num_nodes = distances.size();

    distances[source] = 0;

    // iterrating for n-1 times
    for (int i = 0; i < num_nodes-1; ++i) {
        for (auto& edge : edges) {
            if (distances[edge.src] != INT_MAX) {
                if (distances[edge.src]+edge.weight < distances[edge.dst]) {
                    distances[edge.dst] = distances[edge.src]+edge.weight;
                }
            }
        }
    }

    // doing it once more, if vanu value changes then there is a negative cycle
    bool changed = false;
    for (auto& edge : edges) {
        if (distances[edge.src] != INT_MAX) {
            if (distances[edge.src]+edge.weight < distances[edge.dst]) {
                changed = true;
                distances[edge.dst] = distances[edge.src]+edge.weight;
            }
        }
    }

    if (changed) {
        cout << "Graph contains Negative cycle" << endl;
    }

    return distances;
}

int main() {
    // common graph with weighted Edges
    vector<Edge> edges = {
        Edge{"a","b",3}, Edge{"a","d",6}, Edge{"a","c",9}, Edge{"b","d",4},
        Edge{"b","e",2}, Edge{"b","f",9}, Edge{"b","c",9}, Edge{"c","f",8},
        Edge{"c","j",18}, Edge{"d","g",9}, Edge{"d","e",2}, Edge{"e","g",9},
        Edge{"e","f",8}, Edge{"f","g",7}, Edge{"f","i",9}, Edge{"f","j",10},
        Edge{"g","h",4}, Edge{"g","i",5}, Edge{"h","j",4}, Edge{"h","i",1},
        Edge{"i","j",3}
    };


    auto src_node = "a";

    auto result = bellman_ford(edges, src_node);

    for (auto val : result) {
        cout << val.first << " " << val.second << endl;
    }
    return 0;
}