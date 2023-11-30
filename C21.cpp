#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class UnionFind {
    vector<int> parent;

public:
    UnionFind(int n) : parent(n) {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int i) {
        if (parent[i] != i)
            parent[i] = find(parent[i]);
        return parent[i];
    }

    void unionSet(int a, int b) {
        parent[find(a)] = find(b);
    }

    bool connected(int a, int b) {
        return find(a) == find(b);
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

    void addEdgesFromSet(const vector<pair<int, pair<int, int>>>& S) {
        for (const auto& edge : S) {
            edges.push_back(edge);
        }
    }

    void findMSTIncludingSet(const vector<pair<int, pair<int, int>>>& S) {
        UnionFind uf(V);
        vector<pair<int, pair<int, int>>> mst;

        // Thêm các cạnh từ S trước
        for (const auto& edge : S) {
            if (!uf.connected(edge.second.first, edge.second.second)) {
                uf.unionSet(edge.second.first, edge.second.second);
                mst.push_back(edge);
            }
        }

        // Sắp xếp tất cả các cạnh còn lại theo trọng số
        sort(edges.begin(), edges.end());

        // Thực hiện thuật toán Kruskal với các cạnh còn lại
        for (const auto& edge : edges) {
            if (!uf.connected(edge.second.first, edge.second.second)) {
                uf.unionSet(edge.second.first, edge.second.second);
                mst.push_back(edge);
            }
        }

        // In cây bao trùm nhỏ nhất
        cout << "Minimum Spanning Tree including edges from the set:" << endl;
        for (const auto& edge : mst) {
            cout << edge.second.first << " - " << edge.second.second << " : " << edge.first << endl;
        }
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 15);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 7);
    g.addEdge(4, 0, 8);

    vector<pair<int, pair<int, int>>> S = {{{6, {0, 1}}, {2, {1, 2}}}}; // Tập cạnh S
    g.addEdgesFromSet(S);
    g.findMSTIncludingSet(S);

    return 0;
}

