#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Định nghĩa cấu trúc đỉnh
struct Vertex {
    int id;        // ID của đỉnh
    int distance;  // Khoảng cách ngắn nhất từ nguồn đến đỉnh này
    Vertex(int i, int d) : id(i), distance(d) {}
    bool operator>(const Vertex& other) const {
        return distance > other.distance;
    }
};

// Hàm tìm đường đi ngắn nhất từ một nguồn đến tất cả các đỉnh trong đồ thị
vector<int> dijkstra(const vector<vector<pair<int, int>>>& graph, int source) {
    int V = graph.size();
    vector<int> distance(V, INT_MAX);
    priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;

    // Đưa đỉnh nguồn vào hàng đợi ưu tiên
    pq.push(Vertex(source, 0));
    distance[source] = 0;

    while (!pq.empty()) {
        Vertex u = pq.top();
        pq.pop();

        // Duyệt qua các đỉnh kề của u
        for (const auto& edge : graph[u.id]) {
            int v = edge.first;
            int weight = edge.second;

            // Nếu có một đường đi ngắn hơn đến đỉnh v, cập nhật distance và đưa v vào hàng đợi
            if (distance[u.id] + weight < distance[v]) {
                distance[v] = distance[u.id] + weight;
                pq.push(Vertex(v, distance[v]));
            }
        }
    }

    return distance;
}

int main() {
    int V, E;
    cin >> V >> E; // Nhập số đỉnh và số cạnh của đồ thị

    vector<vector<pair<int, int>>> graph(V); // Đồ thị có hướng với cạnh có trọng số

    // Nhập danh sách các cạnh và trọng số
    for (int i = 0; i < E; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph[u].push_back({v, weight});
    }

    int numSources;
    cin >> numSources; // Số lượng nguồn đường đi ngắn nhất

    // Lưu trữ các nguồn đường đi ngắn nhất
    vector<int> sources(numSources);
    for (int i = 0; i < numSources; ++i) {
        cin >> sources[i];
    }

    // Thêm đỉnh phụ và các cạnh trọng số 0 nối tới các nguồn đường đi ngắn nhất
    int auxiliaryVertex = V;
    for (int source : sources) {
        graph[auxiliaryVertex].push_back({source, 0});
    }

    // Sử dụng thuật toán Dijkstra để tìm đường đi ngắn nhất đa nguồn
    vector<vector<int>> shortestPaths;
    for (int source : sources) {
        vector<int> distances = dijkstra(graph, source);
        shortestPaths.push_back(distances);
    }

    // In kết quả
    for (int i = 0; i < numSources; ++i) {
        cout << "Shortest paths from source " << sources[i] << ":\n";
        for (int j = 0; j < V; ++j) {
            cout << "To vertex " << j << ": " << shortestPaths[i][j] << "\n";
        }
        cout << "\n";
    }

    return 0;
}

