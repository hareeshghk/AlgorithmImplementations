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

unordered_map<string, vector<pair<string,int>>> floydWarshall(vector<Edge> edges) {
    unordered_map<string, vector<pair<string,int>>> result;

    int counter = 0;
    unordered_map<string, int> mapper;
    unordered_map<int, string> rev_mapper;

    for (auto &edge : edges) {
        if (mapper.find(edge.src) == mapper.end()) {
            mapper[edge.src] = counter;
            rev_mapper[counter++] = edge.src;
        }

        if (mapper.find(edge.dst) == mapper.end()) {
            mapper[edge.dst] = counter;
            rev_mapper[counter++] = edge.dst;
        }
    }


    int num_nodes = counter;

    vector<vector<int>> distances(num_nodes, vector<int>(num_nodes, INT_MAX));


    for (auto &edge : edges) {
        distances[mapper[edge.src]][mapper[edge.dst]] = edge.weight;
        distances[mapper[edge.dst]][mapper[edge.src]] = edge.weight;
    }

    for (int i = 0; i < num_nodes; ++i) {
        distances[i][i] = 0;
    }

    for (int k = 0; k < num_nodes; ++k) {
        for (int i = 0; i < num_nodes; ++i) {
            for (int j = 0; j < num_nodes; ++j) {
                if (distances[i][k] != INT_MAX && distances[k][j] != INT_MAX &&
                  (distances[i][j] > (distances[i][k] + distances[k][j]))) {
                    distances[i][j] = distances[i][k] + distances[k][j];
                }
            }
        }
    }

    for (int i = 0; i < num_nodes; ++i) {
        for (int j = 0; j < num_nodes; ++j) {
            result[rev_mapper[i]].push_back(pair<string,int>(rev_mapper[j], distances[i][j]));
        }
    }

    return result;
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

    auto result = floydWarshall(edges);

    for (auto val : result) {
        cout << val.first << " -> { ";
        for (auto nei : val.second) {
            cout << nei.first << ":" << nei.second  << " ";
        }
        cout << " }" << endl;
    }

    return 0;
}