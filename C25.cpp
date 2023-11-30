#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> pii; // Pair: (weight, vertex)

class Graph {
    int V;
    vector<vector<pii>> adj; // Danh sách kề: (vertex, weight)

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w)); // Vì đồ thị không hướng
    }

    void PrimMST() {
        vector<int> key(V, INT_MAX);
        vector<bool> inMST(V, false);
        priority_queue<pii, vector<pii>, greater<pii>> pq;

        // Bắt đầu từ đỉnh 0
        pq.push(make_pair(0, 0));
        key[0] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            inMST[u] = true; // Đánh dấu đỉnh u đã ở trong MST

            // Duyệt qua tất cả các đỉnh kề của u
            for (auto &i : adj[u]) {
                int v = i.first;
                int weight = i.second;

                // Nếu v không nằm trong MST và trọng số của (u, v) nhỏ hơn key[v]
                if (!inMST[v] && key[v] > weight) {
                    key[v] = weight;
                    pq.push(make_pair(key[v], v));
                }
            }
        }

        // In cây bao trùm nhỏ nhất
        for (int i = 1; i < V; ++i)
            cout << i << " - " << key[i] << endl;
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    g.PrimMST();

    return 0;
}

