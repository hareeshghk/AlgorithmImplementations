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

    bool operator() (pair<string, Edge> &a, pair<string, Edge> &b) {
        return a.second.weight > b.second.weight;
    }
};

vector<Edge> prims(vector<Edge> edges) {
    vector<Edge> result;

    unordered_map<string, vector<pair<string,int>>> graph;

    for (int i = 0; i < edges.size(); ++i) {
        auto& edge = edges[i];
        graph[edge.src].push_back(pair<string,int>(edge.dst, i));
        graph[edge.dst].push_back(pair<string,int>(edge.src, i));
    }

    string src_node = "a";
    priority_queue<pair<string, Edge>, vector<pair<string, Edge>>, Edge> pq;
    unordered_set<string> vis;
    vis.insert("a");

    for (auto val : graph[src_node]) {
        pq.push(pair<string,Edge>(val.first, edges[val.second]));
    }

    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();

        if (vis.count(cur.first) != 0) continue;

        vis.insert(cur.first);
        result.push_back(cur.second);

        for (auto nei : graph[cur.first]) {
            pq.push(pair<string, Edge>(nei.first, edges[nei.second]));
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

    auto chosen_edges = prims(edges);

    map<string, vector<pair<string,int>>> graph;

    for (auto edge : chosen_edges) {
        graph[edge.src].push_back(pair<string,int>(edge.dst, edge.weight));
        graph[edge.dst].push_back(pair<string,int>(edge.src, edge.weight));
    }

    for (auto n : graph) {
        cout << n.first << "-> { ";

        for (auto v : n.second) {
            cout << v.first << " ";
        }
        cout << "}" << endl;
    }
    return 0;
}