#include <iostream>
#include <list>
#include <vector>
using namespace std;

class Graph {
    int V; // Số đỉnh
    list<int> *adj; // Danh sách kề

    void DFS(int v, vector<bool> &visited) {
        visited[v] = true;
        for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
            if (!visited[*i])
                DFS(*i, visited);
    }

public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w); // Thêm w vào danh sách kề của v
        adj[w].push_back(v); // Vì đồ thị vô hướng
    }

    bool isConnected() {
        vector<bool> visited(V, false);
        DFS(0, visited);

        for (int i = 0; i < V; i++)
            if (visited[i] == false)
                return false;

        return true;
    }
};

int main() {
    // Tạo đồ thị
    Graph g(5); // Ví dụ với 5 đỉnh
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    // Kiểm tra liên thông cạnh
    cout << "Graph is " << (g.isConnected() ? "connected" : "not connected") << endl;

    return 0;
}

