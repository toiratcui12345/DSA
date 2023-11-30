#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Graph {
    int V;
    vector<pair<int, pair<int, int>>> edges;

    // Hàm tìm chu trình trong MST hiện tại và trả về cạnh lớn nhất trong chu trình
    pair<int, pair<int, int>> findMaxEdgeInCycle(int u, int v, unordered_map<int, vector<pair<int, int>>> &mst, vector<bool> &visited) {
        visited[u] = true;
        if (u == v) return make_pair(-1, make_pair(-1, -1)); // Điểm cuối chu trình

        for (auto &edge : mst[u]) {
            int vertex = edge.first;
            int weight = edge.second;
            if (!visited[vertex]) {
                auto result = findMaxEdgeInCycle(vertex, v, mst, visited);
                if (result.second.first != -1) { // Nếu tìm thấy chu trình
                    if (result.first == -1 || weight > result.first) {
                        return make_pair(weight, make_pair(u, vertex));
                    }
                    return result;
                }
            }
        }

        return make_pair(-1, make_pair(-1, -1));
    }

public:
    Graph(int V) {
        this->V = V;
    }

    void addEdge(int u, int v, int w) {
        edges.push_back({w, {u, v}});
    }

    void VyssotskyMST() {
        sort(edges.begin(), edges.end());
        unordered_map<int, vector<pair<int, int>>> mst;
        unordered_set<int> vertices;

        for (auto &edge : edges) {
            int weight = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;

            mst[u].push_back(make_pair(v, weight));
            mst[v].push_back(make_pair(u, weight));
            vertices.insert(u);
            vertices.insert(v);

            vector<bool> visited(V, false);
            auto maxEdge = findMaxEdgeInCycle(u, v, mst, visited);

            if (maxEdge.second.first != -1) { // Nếu có chu trình
                int u1 = maxEdge.second.first;
                int v1 = maxEdge.second.second;

                // Xóa cạnh lớn nhất trong chu trình
                mst[u1].erase(remove_if(mst[u1].begin(), mst[u1].end(), [v1](const pair<int, int> &edge) { return edge.first == v1; }), mst[u1].end());
                mst[v1].erase(remove_if(mst[v1].begin(), mst[v1].end(), [u1](const pair<int, int> &edge) { return edge.first == u1; }), mst[v1].end());
            }
        }

        // In cây bao trùm nhỏ nhất
        cout << "Edges in the Minimum Spanning Tree:" << endl;
        for (auto &vertex : vertices) {
            for (auto &edge : mst[vertex]) {
                if (vertex < edge.first) { // Đảm bảo mỗi cạnh chỉ được in một lần
                    cout << vertex << " - " << edge.first << " : " << edge.second << endl;
                }
            }
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

    g.VyssotskyMST();

    return 0;
}

