#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
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

    void reverseDeleteMST() {
        sort(edges.rbegin(), edges.rend()); // Sắp xếp cạnh theo trọng số giảm dần
        UnionFind uf(V);

        for (auto it = edges.begin(); it != edges.end();) {
            int u = it->second.first;
            int v = it->second.second;
            int w = it->first;

            // Xóa cạnh nếu nó không làm mất liên thông
            if (uf.connected(u, v)) {
                it = edges.erase(it);
            } else {
                uf.unionSet(u, v);
                ++it;
            }
        }

        // In cây bao trùm nhỏ nhất
        cout << "Edges in the Minimum Spanning Tree:" << endl;
        for (auto &edge : edges) {
            cout << edge.second.first << " - " << edge.second.second << " : " << edge.first << endl;
        }
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    g.reverseDeleteMST();

    return 0;
}

