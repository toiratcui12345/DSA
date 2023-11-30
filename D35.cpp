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

// Hàm để tìm đường đi bitonic ngắn nhất từ đỉnh s tới mỗi đỉnh còn lại
vector<int> findBitonicShortestPath(vector<vector<Vertex>>& graph, int s) {
    int n = graph.size(); // Số đỉnh trong đồ thị
    vector<int> bitonicDist(n, INT_MAX); // Mảng lưu trọng số đường đi bitonic ngắn nhất từ s đến mỗi đỉnh
    vector<int> increasingDist(n, INT_MAX); // Mảng lưu trọng số đường đi tăng dần từ s đến mỗi đỉnh
    vector<int> decreasingDist(n, INT_MAX); // Mảng lưu trọng số đường đi giảm dần từ s đến mỗi đỉnh

    increasingDist[s] = 0; // Trọng số từ s đến chính nó là 0

    // Hàng đợi ưu tiên lưu trữ các đỉnh được xét
    priority_queue<pair<int, int>> pq; // Sử dụng cặp (trọng số, đỉnh) để lấy đỉnh có trọng số nhỏ nhất

    pq.push({0, s}); // Đưa đỉnh s vào hàng đợi

    // Duyệt từ đỉnh s để tính đường đi tăng dần
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Duyệt qua các đỉnh kề của u
        for (const Vertex& v : graph[u]) {
            int alt = increasingDist[u] + v.weight;
            if (alt < increasingDist[v.id]) {
                increasingDist[v.id] = alt;
                pq.push({-alt, v.id}); // Sử dụng dấu âm để đảo chiều ưu tiên
            }
        }
    }

    // Duyệt từ đỉnh s để tính đường đi giảm dần
    pq.push({0, s}); // Đưa đỉnh s vào hàng đợi
    vector<bool> visited(n, false); // Mảng đánh dấu các đỉnh đã xét

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Duyệt qua các đỉnh kề của u
        for (const Vertex& v : graph[u]) {
            int alt = decreasingDist[u] + v.weight;
            if (alt < decreasingDist[v.id]) {
                decreasingDist[v.id] = alt;
                pq.push({-alt, v.id}); // Sử dụng dấu âm để đảo chiều ưu tiên
            }
        }

        visited[u] = true; // Đánh dấu đỉnh u đã xét

        // Khi đã xét tất cả các đỉnh, tính đường đi bitonic ngắn nhất
        bool allVisited = true;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                allVisited = false;
                break;
            }
        }

        if (allVisited) {
            for (int i = 0; i < n; ++i) {
                bitonicDist[i] = increasingDist[i] + decreasingDist[i];
            }
        }
    }

    return bitonicDist;
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

    // Tìm đường đi bitonic ngắn nhất từ s tới mỗi đỉnh
    vector<int> shortestDistances = findBitonicShortestPath(graph, s);

    // In kết quả
    cout << "Ket qua:" << endl;
    for (int i = 0; i < n; ++i) {
        if (i != s) {
            cout << "Tu " << s << " den " << i << ": " << shortestDistances[i] << endl;
        }
    }

    return 0;
}

