#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Hàm để đếm cạnh song song
int countParallelEdges(const vector<pair<int, int>>& edges) {
    unordered_map<string, int> edgeCount;
    int parallelEdges = 0;

    for (const auto& edge : edges) {
        string edgeKey = to_string(min(edge.first, edge.second)) + "-" + to_string(max(edge.first, edge.second));
        edgeCount[edgeKey]++;

        if (edgeCount[edgeKey] > 1) {
            parallelEdges++;
        }
    }

    return parallelEdges;
}

int main() {
    // Ví dụ về danh sách cạnh của đồ thị
    vector<pair<int, int>> edges = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {1, 2}, {2, 3}};

    cout << "Number of parallel edges: " << countParallelEdges(edges) << endl;

    return 0;
}

