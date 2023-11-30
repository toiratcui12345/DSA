#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>

using namespace std;

// Định nghĩa cấu trúc đỉnh
struct Vertex {
    int id;           // ID của đỉnh
    double distance;  // Khoảng cách ngắn nhất từ nguồn đến đỉnh này
    Vertex(int i, double d) : id(i), distance(d) {}
    bool operator>(const Vertex& other) const {
        return distance > other.distance;
    }
};

// Hàm tính khoảng cách giữa hai điểm trên mặt phẳng Euclid
double euclideanDistance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// Hàm tìm đường đi ngắn nhất bằng thuật toán Dijkstra
double shortestPathEuclidean(vector<vector<pair<int, double>>>& graph, int source, int target) {
    int V = graph.size();
    vector<double> distance(V, numeric_limits<double>::max());
    priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;

    distance[source] = 0;
    pq.push(Vertex(source, 0));

    while (!pq.empty()) {
        Vertex u = pq.top();
        pq.pop();

        if (u.id == target) {
            return u.distance;
        }

        for (const auto& edge : graph[u.id]) {
            int v = edge.first;
            double weight = edge.second;

            double newDistance = distance[u.id] + weight;

            if (newDistance < distance[v]) {
                distance[v] = newDistance;
                pq.push(Vertex(v, newDistance));
            }
        }
    }

    return -1; // Không tìm thấy đường đi
}

int main() {
    int V, E;
    cin >> V >> E; // Nhập số đỉnh và số cạnh của đồ thị

    vector<vector<pair<int, double>>> graph(V); // Đồ thị với trọng số là khoảng cách Euclid

    // Nhập tọa độ các điểm trên mặt phẳng
    vector<pair<double, double>> coordinates(V);
    for (int i = 0; i < V; ++i) {
        cin >> coordinates[i].first >> coordinates[i].second;
    }

    // Tạo đồ thị với trọng số là khoảng cách Euclid giữa các điểm
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        double distance = euclideanDistance(coordinates[u].first, coordinates[u].second, coordinates[v].first, coordinates[v].second);
        graph[u].push_back({v, distance});
        graph[v].push_back({u, distance}); // Đồ thị vô hướng
    }

    int source, target;
    cin >> source >> target; // Nhập đỉnh nguồn và đích

    // Tìm đường đi ngắn nhất giữa hai đỉnh trên đồ thị Euclid
    double shortestDistance = shortestPathEuclidean(graph, source, target);

    if (shortestDistance != -1) {
        cout << "Shortest distance between source and target: " << shortestDistance << endl;
    } else {
        cout << "No path exists between source and target." << endl;
    }

    return 0;
}

