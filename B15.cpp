#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;

class Graph {
    int V;
    list<int> *adj;

public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void topologicalSort() {
        vector<int> indegree(V, 0);

        // Tính bậc vào cho mỗi đỉnh
        for (int i = 0; i < V; i++) {
            for (int v : adj[i]) {
                indegree[v]++;
            }
        }

        // Hàng đợi để lưu trữ các đỉnh có indegree bằng 0
        queue<int> q;
        for (int i = 0; i < V; i++)
            if (indegree[i] == 0)
                q.push(i);

        // Duyệt qua đồ thị
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";

            // Giảm indegree của mỗi đỉnh kề và thêm vào hàng đợi nếu indegree bằng 0
            for (int v : adj[u]) {
                if (--indegree[v] == 0)
                    q.push(v);
            }
        }
    }
};

int main() {
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    cout << "Topological sort of the given graph:" << endl;
    g.topologicalSort();

    return 0;
}

