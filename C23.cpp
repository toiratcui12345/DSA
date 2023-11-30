#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class UnionFind {
    vector<int> parent, rank;

public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int i) {
        if (parent[i] != i)
            parent[i] = find(parent[i]);
        return parent[i];
    }

    void unionSet(int x, int y) {
        int xRoot = find(x), yRoot = find(y);
        if (rank[xRoot] < rank[yRoot])
            parent[xRoot] = yRoot;
        else if (rank[xRoot] > rank[yRoot])
            parent[yRoot] = xRoot;
        else if (xRoot != yRoot) {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }
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

    void BoruvkaMST() {
        UnionFind uf(V);
        vector<pair<int, pair<int, int>>> mst;

        while (mst.size() < V - 1) {
            vector<pair<int, int>> cheapest(V, {-1, -1});

            for (auto& edge : edges) {
                int weight = edge.first;
                int u = edge.second.first;
                int v = edge.second.second;
                int setU = uf.find(u), setV = uf.find(v);
                if (setU != setV) {
                    if (cheapest[setU].second == -1 || cheapest[setU].first > weight)
                        cheapest[setU] = {weight, v};
                    if (cheapest[setV].second == -1 || cheapest[setV].first > weight)
                        cheapest[setV] = {weight, u};
                }
            }

            for (int i = 0; i < V; ++i) {
                if (cheapest[i].second != -1 && !uf.connected(i, cheapest[i].second)) {
                    mst.push_back({cheapest[i].first, {i, cheapest[i].second}});
                    uf.unionSet(i, cheapest[i].second);
                }
            }
        }

        // In cây bao trùm nhỏ nhất
        cout << "Edges in the Minimum Spanning Tree:" << endl;
        for (auto &edge : mst)
            cout << edge.second.first << " - " << edge.second.second << " : " << edge.first << endl;
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    g.BoruvkaMST();

    return 0;
}

