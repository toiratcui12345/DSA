
#include <iostream>
using namespace std;

long long power(long long base, int exponent) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result *= base;
        exponent /= 2;
        base *= base;
    }
    return result;
}

int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;

    long long numberOfDAGs = power(3, (V * (V - 1)) / 2);
    cout << "Number of directed acyclic graphs with " << V << " vertices: " << numberOfDAGs << endl;

    return 0;
}

