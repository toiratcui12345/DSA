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

// Hàm tìm đường đi ngắn nhất giữa hai tập đỉnh S và T
int shortestPathBetweenSets(const vector<vector<pair<int, int>>>& graph, const vector<int>& S, const vector<int>& T) {
    int V = graph.size();
    vector<int> distance(V, INT_MAX);
    priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;

    // Thêm đỉnh phụ và các cạnh trọng số 0 nối tới các đỉnh trong tập S
    int auxiliaryVertex = V;
    for (int s : S) {
        graph[auxiliaryVertex].push_back({s, 0});
    }

    // Đưa đỉnh phụ vào hàng đợi ưu tiên
    pq.push(Vertex(auxiliaryVertex, 0));
    distance[auxiliaryVertex] = 0;

    while (!pq.empty()) {
        Vertex u = pq.top();
        pq.pop();

        // Nếu đỉnh u thuộc tập T, trả về khoảng cách ngắn nhất từ tập S đến tập T
        if (find(T.begin(), T.end(), u.id) != T.end()) {
            return u.distance;
        }

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

    // Không tìm thấy đường đi từ S đến T
    return -1;
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

    int numS, numT;
    cin >> numS; // Số lượng đỉnh trong tập S

    // Lưu trữ các đỉnh trong tập S
    vector<int> S(numS);
    for (int i = 0; i < numS; ++i) {
        cin >> S[i];
    }

    cin >> numT; // Số lượng đỉnh trong tập T

    // Lưu trữ các đỉnh trong tập T
    vector<int> T(numT);
    for (int i = 0; i < numT; ++i) {
        cin >> T[i];
    }

    // Tìm đường đi ngắn nhất giữa tập S và T
    int shortestDistance = shortestPathBetweenSets(graph, S, T);

    if (shortestDistance != -1) {
        cout << "Shortest distance between sets S and T: " << shortestDistance << endl;
    } else {
        cout << "No path exists between sets S and T." << endl;
    }

    return 0;
}

