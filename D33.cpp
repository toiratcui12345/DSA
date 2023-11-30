#include <iostream>
#include <vector>

using namespace std;

int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size();    // Số hàng
    int n = grid[0].size(); // Số cột

    // Tạo một ma trận dp có cùng kích thước với ma trận grid để lưu trữ độ dài ngắn nhất đến mỗi ô
    vector<vector<int>> dp(m, vector<int>(n, 0));

    // Khởi tạo giá trị đầu tiên trong ma trận dp
    dp[0][0] = grid[0][0];

    // Khởi tạo giá trị cho hàng đầu tiên
    for (int i = 1; i < m; ++i) {
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    }

    // Khởi tạo giá trị cho cột đầu tiên
    for (int j = 1; j < n; ++j) {
        dp[0][j] = dp[0][j - 1] + grid[0][j];
    }

    // Tính toán giá trị dp cho các ô còn lại
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            // Chọn đường đi ngắn nhất từ trên hoặc từ trái
            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
        }
    }

    // Trả về độ dài đường đi ngắn nhất đến ô (m-1, n-1)
    return dp[m - 1][n - 1];
}

int main() {
    // Nhập ma trận NxN
    int N;
    cout << "Nhap kich thuoc ma tran N: ";
    cin >> N;

    vector<vector<int>> grid(N, vector<int>(N));
    cout << "Nhap cac phan tu cua ma tran:" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }

    // Tìm đường đi ngắn nhất
    int shortestPath = minPathSum(grid);

    cout << "Do dai duong di ngan nhat: " << shortestPath << endl;

    return 0;
}

