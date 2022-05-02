#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <unordered_map>

using namespace std;


struct Edge {
    string src;
    string dst;
    int weight;

    bool operator() (Edge a, Edge b) {
        return a.weight > b.weight;
    }
};


class DSU {
    vector<int> parent;
    vector<int> rank;
    int capacity;
public:
    DSU(int capacity) {
        this->capacity = capacity;
        parent.resize(capacity);
        rank.resize(capacity, 1);

        for (int i = 0; i < capacity; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unionize(int a, int b) {
        int pa = find(a);
        int pb = find(b);

        if (pa == pb) return false;

        if (rank[pa] >= rank[pb]) {
            rank[pa] += rank[pb];
            parent[pb] = pa;
        } else {
            rank[pb] += rank[pa];
            parent[pa] = pb;
        }
        return true;
    }

    int GetSize(int a) {
        return rank[find(a)];
    }
};

vector<Edge> Kruskal(vector<Edge> edges) {
    unordered_map<string, int> mapper;
    priority_queue<Edge, vector<Edge>, Edge> minheap;

    int num_nodes = 0;

    for (auto edge : edges) {
        if (mapper.find(edge.src) == mapper.end()) {
            mapper[edge.src] = num_nodes++;
        }

        if (mapper.find(edge.dst) == mapper.end()) {
            mapper[edge.dst] = num_nodes++;
        }
        minheap.push(edge);
    }

    // vectore to store resultant edges
    vector<Edge> result;

    DSU d(num_nodes);

    while (!minheap.empty()) {
        auto curEdge = minheap.top();
        minheap.pop();

        if (d.unionize(mapper[curEdge.src], mapper[curEdge.dst])) {
            result.push_back(curEdge);
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

    auto chosen_edges = Kruskal(edges);

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