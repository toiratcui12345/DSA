#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
    int V;
    vector<pair<int, pair<int, int>>> edges;

public:
    Graph(int V) {
        this->V = V;
    }

    void addEdge(int u, int v, int w) {
        edges.push_back({w, {u, v}});
    }

    // Tìm gốc của nút trong disjoint set
    int find(vector<int> &parent, int i) {
        if (parent[i] == -1)
            return i;
        return find(parent, parent[i]);
    }

    // Gộp hai tập hợp
    void unionSet(vector<int> &parent, int x, int y) {
        int xset = find(parent, x);
        int yset = find(parent, y);
        if (xset != yset) {
            parent[xset] = yset;
        }
    }

    // Tính rừng bao trùm nhỏ nhất
    void KruskalMST() {
        vector<pair<int, pair<int, int>>> result;
        sort(edges.begin(), edges.end());
        vector<int> parent(V, -1);

        for (auto &edge : edges) {
            int w = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;

            int set_u = find(parent, u);
            int set_v = find(parent, v);

            if (set_u != set_v) {
                result.push_back({w, {u, v}});
                unionSet(parent, set_u, set_v);
            }
        }

        // In kết quả
        cout << "Edges in the Minimum Spanning Forest:" << endl;
        for (auto &edge : result)
            cout << edge.second.first << " - " << edge.second.second << " : " << edge.first << endl;
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 15);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 0, 6);
    g.addEdge(0, 2, 5);

    g.KruskalMST();

    return 0;
}

