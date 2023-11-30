#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Định nghĩa cấu trúc của một cạnh trong đồ thị có hướng
struct Edge {
    int src;     // Đỉnh nguồn
    int dest;    // Đỉnh đích
    int weight;  // Trọng số của cạnh

    Edge(int _src, int _dest, int _weight) : src(_src), dest(_dest), weight(_weight) {}
};

// Hàm để tìm cạnh cực đại trong đồ thị
Edge findCriticalEdge(vector<vector<Edge>>& graph, int s, int t) {
    int n = graph.size(); // Số đỉnh trong đồ thị
    vector<int> dist(n, INT_MAX); // Mảng lưu trọng số đường đi ngắn nhất từ s đến mỗi đỉnh
    vector<int> parent(n, -1); // Mảng lưu đỉnh cha trên đường đi ngắn nhất

    // Hàng đợi ưu tiên lưu trữ các đỉnh được xét
    priority_queue<pair<int, int>> pq; // Sử dụng cặp (trọng số, đỉnh) để lấy đỉnh có trọng số nhỏ nhất

    dist[s] = 0; // Trọng số từ s đến chính nó là 0

    pq.push({0, s}); // Đưa đỉnh s vào hàng đợi

    // Duyệt từ đỉnh s để tính đường đi ngắn nhất
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Duyệt qua các cạnh kề của u
        for (const Edge& edge : graph[u]) {
            int v = edge.dest;
            int weight = edge.weight;

            // Nếu tìm thấy đường đi ngắn hơn từ s tới v
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({-dist[v], v}); // Sử dụng dấu âm để đảo chiều ưu tiên
            }
        }
    }

    // Tìm đỉnh t trên đường đi ngắn nhất từ s
    int current = t;
    int maxDist = dist[t];

    // Duyệt ngược từ t lên đỉnh s để tìm cạnh cực đại
    while (parent[current] != -1) {
        int u = parent[current];

        // Duyệt qua các cạnh kề của u để tìm cạnh cực đại
        for (const Edge& edge : graph[u]) {
            if (edge.dest == current && dist[u] + edge.weight == maxDist) {
                return edge; // Trả về cạnh cực đại
            }
        }

        current = u;
    }

    // Nếu không tìm thấy cạnh cực đại, trả về một cạnh không hợp lệ
    return Edge(-1, -1, -1);
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

    int s, t; // Đỉnh xuất phát (s) và đỉnh đích (t)
    cout << "Nhap dinh xuoc phat (s) va dinh dich (t): ";
    cin >> s >> t;

    // Tìm cạnh cực đại
    Edge criticalEdge = findCriticalEdge(graph, s, t);

    // In kết quả
    if (criticalEdge.src == -1) {
        cout << "Khong tim thay canh cuc dai" << endl;
    } else {
        cout << "Canh cuc dai la tu " << criticalEdge.src << " den " << criticalEdge.dest << " voi trong so la " << criticalEdge.weight << endl;
    }

    return 0;
}

