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

map<string, int> dijikistra(vector<Edge> edges, string source) {
    int num_nodes;
    map<string, int> distances;

    num_nodes = distances.size();

    unordered_map<string, vector<pair<string, int>>> graph;

    for (auto& edge : edges) {
        graph[edge.src].push_back(pair<string,int>(edge.dst, edge.weight));
        graph[edge.dst].push_back(pair<string,int>(edge.src, edge.weight));
    }

    function<bool(pair<string,int>&, pair<string,int>&)> minpair = [](pair<string,int> &a, pair<string, int> &b) {
        return a.second > b.second;
    };

    priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(minpair)> pq(minpair);

    pq.push(pair<string,int>(source, 0));

    while (!pq.empty()) {
        auto curpair = pq.top();
        pq.pop();

        if (distances.find(curpair.first) != distances.end()) continue;

        distances[curpair.first] = curpair.second;

        for (auto nei : graph[curpair.first]) {
            if (distances.find(nei.first) != distances.end()) continue;
            pq.push(pair<string, int>(nei.first, curpair.second+nei.second));
        }
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

    auto result = dijikistra(edges, src_node);

    for (auto val : result) {
        cout << val.first << " " << val.second << endl;
    }

    return 0;
}