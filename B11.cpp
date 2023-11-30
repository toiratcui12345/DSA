#include <iostream>
#include <list>
#include <stack>
#include <vector>
using namespace std;

class Graph {
    int V;
    list<int> *adj;

    void topologicalSortUtil(int v, vector<bool> &visited, stack<int> &Stack) {
        visited[v] = true;
        for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
            if (!visited[*i])
                topologicalSortUtil(*i, visited, Stack);
        Stack.push(v);
    }

public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    bool isHamiltonianPath() {
        stack<int> Stack;
        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++)
            if (visited[i] == false)
                topologicalSortUtil(i, visited, Stack);

        int u = Stack.top();
        Stack.pop();
        while (!Stack.empty()) {
            int v = Stack.top();
            Stack.pop();

            // Kiểm tra xem có cạnh từ u đến v không
            auto it = find(adj[u].begin(), adj[u].end(), v);
            if (it == adj[u].end())
                return false;
            u = v;
        }
        return true;
    }
};

int main() {
    // Tạo đồ thị
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    cout << "The given graph " << (g.isHamiltonianPath() ? "has" : "does not have") << " a Hamiltonian path." << endl;

    return 0;
}

