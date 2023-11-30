/*
Chu trình Euler và chu trình Hamilton:

Chu trình Euler: Một đồ thị vô hướng có chu trình Euler nếu và chỉ nếu tất cả các đỉnh đều có bậc chẵn.
Có thể kiểm tra điều này bằng cách đếm bậc của từng đỉnh.
Chu trình Hamilton: Việc kiểm tra sự tồn tại của chu trình Hamilton trong một đồ thị là một bài toán NP-đầy đủ và không có thuật toán hiệu quả biết trước cho trường hợp tổng quát.

Để kiểm tra xem một đồ thị có chu trình Hamilton hay không, ta có thể sử dụng định lý sau: Một đồ thị vô hướng liên thông có chu trình Hamilton khi và chỉ khi nó thỏa mãn điều kiện Ore: Với mọi cặp đỉnh u, v không kề nhau, ta có bậc(u) + bậc(v) ≥ n, trong đó n là số đỉnh của đồ thị.
Đồ thị được cho bởi tập cạnh đầu tiên có chu trình Euler, vì tất cả các đỉnh của nó đều có bậc chẵn. Tuy nhiên, đồ thị này không có chu trình Hamilton, vì nó không thỏa mãn điều kiện Ore. Ví dụ, với u = 0 và v = 4, ta có bậc(u) + bậc(v) = 3 + 2 = 5 < 10 = n.
Đồ thị được cho bởi tập cạnh thứ hai không có chu trình Euler, vì có hai đỉnh có bậc lẻ là 0 và 6. Đồ thị này cũng không có chu trình Hamilton, vì nó không thỏa mãn điều kiện Ore. Ví dụ, với u = 0 và v = 4, ta có bậc(u) + bậc(v) = 4 + 2 = 6 < 10 = n.
Đồ thị được cho bởi tập cạnh thứ ba có chu trình Euler, vì tất cả các đỉnh của nó đều có bậc chẵn. Đồ thị này cũng có chu trình Hamilton, vì nó thỏa mãn điều kiện Ore. Ví dụ, với u = 0 và v = 4, ta có bậc(u) + bậc(v) = 4 + 4 = 8 ≥ 10 = n.
Đồ thị được cho bởi tập cạnh thứ tư không có chu trình Euler, vì có hai đỉnh có bậc lẻ là 0 và 9. Đồ thị này cũng không có chu trình Hamilton, vì nó không thỏa mãn điều kiện Ore. Ví dụ, với u = 0 và v = 1, ta có bậc(u) + bậc(v) = 3 + 2 = 5 < 10 = n.

*/
//Example code:
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

    bool isConnected() {
        vector<bool> visited(V, false);
        int i;
        for (i = 0; i < V; i++)
            if (adj[i].size() != 0)
                break;

        if (i == V)
            return true;

        DFS(i, visited);
        for (int i = 0; i < V; i++)
            if (visited[i] == false && adj[i].size() > 0)
                return false;

        return true;
    }

public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    bool isEulerianCycle() {
        if (!isConnected())
            return false;

        for (int i = 0; i < V; i++)
            if (adj[i].size() & 1)
                return false;

        return true;
    }
};

int main() {
    // Tạo đồ thị và thêm cạnh
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0);

    cout << "The graph is " << (g.isEulerianCycle() ? "" : "not ") << "an Eulerian cycle" << endl;

    return 0;
}
