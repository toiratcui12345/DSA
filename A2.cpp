#include <iostream>
using namespace std;

// Hàm tính giai thừa
long long factorial(int n) {
    long long fact = 1;
    for (int i = 2; i <= n; i++)
        fact *= i;
    return fact;
}

// Hàm tính tổ hợp chập k của n
long long binomialCoefficient(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

// Hàm tính số lượng đồ thị khác nhau
long long countGraphs(int V, int E) {
    // Tổ hợp chập E của (V choose 2)
    return binomialCoefficient((V * (V - 1)) / 2, E);
}

int main() {
    int V = 5; // Số đỉnh
    int E = 3; // Số cạnh

    cout << "Number of distinct graphs with " << V
         << " vertices and " << E << " edges: "
         << countGraphs(V, E) << endl;

    return 0;
}

