#include <iostream>
#include <list>
#include <vector>
#include <stack>
using namespace std;

class Graph {
    int V; // Số lượng đỉnh
    list<int> *adj; // Danh sách kề

public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // Kiểm tra xem đồ thị có Eulerian cycle hay không
    bool isEulerianCycle() {
        vector<int> in(V, 0), out(V, 0);

        for (int i = 0; i < V; i++) {
            for (int v : adj[i]) {
                out[i]++;
                in[v]++;
            }
        }

        for (int i = 0; i < V; i++)
            if (in[i] != out[i])
                return false;

        return true;
    }

    void DFS(int v, vector<bool> &visited) {
        visited[v] = true;
        for (int u : adj[v])
            if (!visited[u])
                DFS(u, visited);
    }

    bool isConnected() {
        vector<bool> visited(V, false);
        int i;
        for (i = 0; i < V; i++)
            if (adj[i].size() > 0)
                break;

        if (i == V)
            return true;

        DFS(i, visited);

        for (i = 0; i < V; i++)
            if (adj[i].size() > 0 && !visited[i])
                return false;

        return true;
    }

    // Hàm để tìm và in ra chu trình Euler
    void printEulerianCycle() {
        if (!isConnected() || !isEulerianCycle()) {
            cout << "Không tồn tại chu trình Euler";
            return;
        }

        stack<int> curr_path;
        vector<int> cycle;
        curr_path.push(0);

        while (!curr_path.empty()) {
            int curr = curr_path.top();
            if (adj[curr].size()) {
                curr_path.push(adj[curr].front());
                adj[curr].pop_front();
            } else {
                cycle.push_back(curr);
                curr_path.pop();
            }
        }

        for (int i = cycle.size() - 1; i >= 0; i--)
            cout << cycle[i] << " ";
    }
};

int main() {
    Graph g(3);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);

    g.printEulerianCycle();

    return 0;
}

