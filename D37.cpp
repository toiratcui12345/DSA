#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int src;
    int dest;
    int weight;

    Edge(int _src, int _dest, int _weight) : src(_src), dest(_dest), weight(_weight) {}
};

void bellmanFordFast(vector<vector<Edge>>& graph, int s, int C) {
    int n = graph.size();
    vector<int> maxDist(C + 1, INT_MAX); // Mảng lưu trữ khoảng cách tối đa theo độ dài đường đi
    vector<int> nextMaxDist(C + 1, INT_MAX); // Mảng lưu trữ khoảng cách tối đa tạm thời

    maxDist[0] = 0; // Khoảng cách từ s đến chính nó là 0

    for (int d = 1; d <= C; ++d) {
        for (int u = 0; u < n; ++u) {
            nextMaxDist[d] = maxDist[d - 1]; // Gán giá trị mặc định

            for (const Edge& edge : graph[u]) {
                int v = edge.dest;
                int weight = edge.weight;

                if (d >= weight) {
                    nextMaxDist[d] = max(nextMaxDist[d], maxDist[d - weight] + weight);
                }
            }
        }

        maxDist.swap(nextMaxDist); // Swap mảng tạm thời với mảng chính
    }

    // In kết quả
    for (int d = 1; d <= C; ++d) {
        cout << "Khoang cach toi da " << d << ": " << maxDist[d] << endl;
    }
}

int main() {
    int n, m; // Số đỉnh và số cạnh của đồ thị
    cout << "Nhap so dinh va so canh cua do thi: ";
    cin >> n >> m;

    vector<vector<Edge>> graph(n); // Danh sách kề lưu trữ đồ thị

    // Nhập thông tin các cạnh của đồ thị
    for (int i = 0; i < m; ++i) {
        int u, v, weight;
        cout << "Nhap thong tin cua canh thu " << i + 1 << " (u, v, weight): ";
        cin >> u >> v >> weight;

        // Thêm cạnh vào đồ thị
        graph[u].emplace_back(u, v, weight);
    }

    int s, C; // Đỉnh xuất phát (s) và hằng số C
    cout << "Nhap dinh xuoc phat (s) va hang so C: ";
    cin >> s >> C;

    // Tìm khoảng cách tối đa từ s đến các đỉnh
    bellmanFordFast(graph, s, C);

    return 0;
}

