#include <iostream>
#include <vector>
using namespace std;

void floodFillUtil(vector<vector<int>> &screen, int x, int y, int prevC, int newC) {
    int M = screen.size();
    int N = screen[0].size();

    if (x < 0 || x >= M || y < 0 || y >= N)
        return;
    if (screen[x][y] != prevC)
        return;

    screen[x][y] = newC;

    floodFillUtil(screen, x+1, y, prevC, newC);
    floodFillUtil(screen, x-1, y, prevC, newC);
    floodFillUtil(screen, x, y+1, prevC, newC);
    floodFillUtil(screen, x, y-1, prevC, newC);
}

void floodFill(vector<vector<int>> &screen, int x, int y, int newC) {
    int prevC = screen[x][y];
    floodFillUtil(screen, x, y, prevC, newC);
}

int main() {
    vector<vector<int>> screen = {{1, 1, 1, 1},
                                  {1, 1, 0, 1},
                                  {1, 0, 3, 3}};

    floodFill(screen, 1, 1, 2); // Đổi màu khu vực từ (1,1) từ màu 1 sang màu 2

    // In kết quả
    for (int i = 0; i < screen.size(); i++) {
        for (int j = 0; j < screen[i].size(); j++)
            cout << screen[i][j] << " ";
        cout << endl;
    }

    return 0;
}

