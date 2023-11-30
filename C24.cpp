#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

class Edge {
public:
    int u, v, weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

class Graph {
    int V;
    vector<list<Edge>> adj; // Danh sách kề cho mỗi đỉnh

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int u, int v, int weight) {
        adj[u].push_back(Edge(u, v, weight));
        adj[v].push_back(Edge(v, u, weight)); // Vì đồ thị không hướng
    }

    void BoruvkaMST() {
        vector<int> component(V); // Thành phần mà mỗi đỉnh thuộc về
        vector<Edge> cheapest(V); // Cạnh rẻ nhất nối thành phần này với thành phần khác

        iota(component.begin(), component.end(), 0); // Khởi tạo mỗi đỉnh là một thành phần riêng biệt

        int numTrees = V;
        int MSTweight = 0;

        // Lặp cho đến khi chỉ còn một cây
        while (numTrees > 1) {
            fill(cheapest.begin(), cheapest.end(), Edge(-1, -1, INT_MAX));

            // Tìm cạnh rẻ nhất cho mỗi thành phần
            for (int u = 0; u < V; ++u) {
                for (const Edge &e : adj[u]) {
                    int compU = component[u];
                    int compV = component[e.v];
                    if (compU != compV && e.weight < cheapest[compU].weight) {
                        cheapest[compU] = e;
                    }
                }
            }

            // Kết nối các thành phần lại với nhau
            for (int comp = 0; comp < V; ++comp) {
                if (cheapest[comp].u != -1) {
                    int u = cheapest[comp].u, v = cheapest[comp].v, w = cheapest[comp].weight;
                    if (component[u] != component[v]) {
                        MSTweight += w;
                        cout << "Edge " << u << " - " << v << " in MST" << endl;

                        // Merge hai thành phần
                        int oldComp = component[v], newComp = component[u];
                        for (int i = 0; i < V; ++i) {
                            if (component[i] == oldComp)
                                component[i] = newComp;
                        }
                        numTrees--;
                    }
                }
            }
        }

        cout << "Weight of MST is " << MSTweight << endl;
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 6);
    g.addEdge(2, 3, 5);
    g.addEdge(3, 0, 15);

    g.BoruvkaMST();

    return 0;
}
