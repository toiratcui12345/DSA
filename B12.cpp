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

    bool hasUniqueTopologicalSort() {
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
                return false; // Không có cạnh từ u đến v, thứ tự tô pô không duy nhất
            u = v;
        }
        return true; // Có cạnh từ mỗi đỉnh đến đỉnh kế tiếp, thứ tự tô pô duy nhất
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    cout << "The given graph " << (g.hasUniqueTopologicalSort() ? "has" : "does not have") << " a unique topological order." << endl;

    return 0;
}

