#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class UnionFind {
    vector<int> parent;
public:
    UnionFind(int size) : parent(size) {
        for (int i = 0; i < size; ++i) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    void unionSet(int x, int y) {
        parent[find(x)] = find(y);
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

class Graph {
    int V;
    vector<pair<int, pair<int, int>>> edges;

public:
    Graph(int V) : V(V) {}

    void addEdge(int u, int v, int w) {
        edges.push_back({w, {u, v}});
    }

    void findCriticalEdges() {
        sort(edges.begin(), edges.end());
        UnionFind uf(V);
        vector<pair<int, pair<int, int>>> mst;

        for (auto &edge : edges) {
            int u = edge.second.first;
            int v = edge.second.second;
            if (!uf.connected(u, v)) {
                uf.unionSet(u, v);
                mst.push_back(edge);
            }
        }

        // Kiểm tra cạnh khó
        for (auto &edge : mst) {
            int u = edge.second.first;
            int v = edge.second.second;
            int weight = edge.first;
            UnionFind tempUf(V);
            for (auto &tempEdge : edges) {
                if (tempEdge != edge) {
                    int tempU = tempEdge.second.first;
                    int tempV = tempEdge.second.second;
                    if (!tempUf.connected(tempU, tempV)) {
                        tempUf.unionSet(tempU, tempV);
                    }
                }
            }
            if (!tempUf.connected(u, v)) {
                cout << "Critical edge: " << u << " - " << v << " with weight " << weight << endl;
            }
        }
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 0, 4);
    g.addEdge(0, 2, 5);

    g.findCriticalEdges();

    return 0;
}

