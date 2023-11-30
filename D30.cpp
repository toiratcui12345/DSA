#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Định nghĩa cấu trúc đỉnh
struct Vertex {
    int id;           // ID của đỉnh
    double distance;  // Khoảng cách dài nhất từ nguồn đến đỉnh này
    Vertex(int i, double d) : id(i), distance(d) {}
    bool operator<(const Vertex& other) const {
        return distance < other.distance;
    }
};

// Hàm tìm đường đi dài nhất trong DAG
double longestPathDAG(vector<vector<pair<int, double>>>& graph, int source, int target) {
    int V = graph.size();
    vector<double> distance(V, numeric_limits<double>::lowest());
    priority_queue<Vertex> pq;

    distance[source] = 0;
    pq.push(Vertex(source, 0));

    while (!pq.empty()) {
        Vertex u = pq.top();
        pq.pop();

        if (u.id == target) {
            return -distance[target]; // Khoảng cách dài nhất là âm của khoảng cách lưu trong distance
        }

        for (const auto& edge : graph[u.id]) {
            int v = edge.first;
            double weight = edge.second;

            double newDistance = -distance[u.id] + weight;

            if (newDistance > distance[v]) {
                distance[v] = newDistance;
                pq.push(Vertex(v, -newDistance));
            }
        }
    }

    return -1; // Không tìm thấy đường đi
}

int main() {
    int V, E;
    cin >> V >> E; // Nhập số đỉnh và số cạnh của đồ thị

    vector<vector<pair<int, double>>> graph(V); // Đồ thị có trọng số

    // Nhập cạnh và trọng số
    for (int i = 0; i < E; ++i) {
        int u, v;
        double weight;
        cin >> u >> v >> weight;
        graph[u].push_back({v, weight});
    }

    int source, target;
    cin >> source >> target; // Nhập đỉnh nguồn và đích

    // Tìm đường đi dài nhất trong DAG
    double longestDistance = longestPathDAG(graph, source, target);

    if (longestDistance != -1) {
        cout << "Longest distance between source and target: " << longestDistance << endl;
    } else {
        cout << "No path exists between source and target." << endl;
    }

    return 0;
}

