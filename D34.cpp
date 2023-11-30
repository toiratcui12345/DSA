#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Định nghĩa cấu trúc của một đỉnh trong đồ thị
struct Vertex {
    int id;           // ID của đỉnh
    int weight;       // Trọng số của đỉnh

    Vertex(int _id, int _weight) : id(_id), weight(_weight) {}
};

// Định nghĩa cạnh của đồ thị
struct Edge {
    int src;     // Đỉnh nguồn
    int dest;    // Đỉnh đích
    int weight;  // Trọng số của cạnh

    Edge(int _src, int _dest, int _weight) : src(_src), dest(_dest), weight(_weight) {}
};

// Hàm để tìm đường đi đơn điệu ngắn nhất từ đỉnh s tới mỗi đỉnh còn lại
vector<int> findMonotonicShortestPath(vector<vector<Vertex>>& graph, int s) {
    int n = graph.size(); // Số đỉnh trong đồ thị
    vector<int> dist(n, INT_MAX); // Mảng lưu trọng số đường đi ngắn nhất từ s đến mỗi đỉnh
    dist[s] = 0; // Trọng số từ s đến chính nó là 0

    // Hàng đợi ưu tiên lưu trữ các đỉnh được xét
    priority_queue<pair<int, int>> pq; // Sử dụng cặp (trọng số, đỉnh) để lấy đỉnh có trọng số nhỏ nhất

    pq.push({0, s}); // Đưa đỉnh s vào hàng đợi

    // Duyệt từ đỉnh s
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Duyệt qua các đỉnh kề của u
        for (const Vertex& v : graph[u]) {
            int alt = dist[u] + v.weight;
            if (alt < dist[v.id]) {
                dist[v.id] = alt;
                pq.push({-alt, v.id}); // Sử dụng dấu âm để đảo chiều ưu tiên
            }
        }
    }

    return dist;
}

int main() {
    int n, m; // Số đỉnh và số cạnh của đồ thị
    cout << "Nhap so dinh va so canh cua do thi: ";
    cin >> n >> m;

    vector<vector<Vertex>> graph(n); // Danh sách kề lưu trữ đồ thị

    // Nhập thông tin các đỉnh và cạnh của đồ thị
    for (int i = 0; i < m; ++i) {
        int u, v, weight;
        cout << "Nhap thong tin cua canh thu " << i + 1 << " (u, v, weight): ";
        cin >> u >> v >> weight;

        // Thêm cạnh vào đồ thị
        graph[u].emplace_back(v, weight);
        graph[v].emplace_back(u, weight); // Nếu đồ thị vô hướng
    }

    int s; // Đỉnh xuất phát
    cout << "Nhap dinh xuat phat: ";
    cin >> s;

    // Tìm đường đi đơn điệu ngắn nhất từ s tới mỗi đỉnh
    vector<int> shortestDistances = findMonotonicShortestPath(graph, s);

    // In kết quả
    cout << "Ket qua:" << endl;
    for (int i = 0; i < n; ++i) {
        if (i != s) {
            cout << "Tu " << s << " den " << i << ": " << shortestDistances[i] << endl;
        }
    }

    return 0;
}

