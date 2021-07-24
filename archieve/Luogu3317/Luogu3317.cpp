#include <array>
#include <iostream>
#include <vector>
using namespace std;
const long double eps = 1e-10;
struct Matrix {
    vector<vector<long double>> arr;
    int n;
    Matrix() {
    }
    Matrix(int n) {
        this->n = n;
        arr     = vector<vector<long double>>(n, vector<long double>(n));
    }
    auto &operator[](const int x) {
        return arr[x];
    }
};
double det(Matrix M) {
    long double res;
    res   = 1;
    int n = M.n;
    for (int i = 0; i < n; i++) {
        res      = res * M[i][i];
        auto tmp = 1.0 / M[i][i];
        for (int j = i; j < n; j++) {
            M[i][j] = M[i][j] * tmp;
        }
        for (int j = i + 1; j < n; j++) {
            auto tmp = M[j][i];
            for (int k = i; k < n; k++) {
                M[j][k] = M[j][k] - tmp * M[i][k];
            }
        }
    }
    return res;
}
int n;
int main() {
    cin >> n;
    Matrix L(n);
    double ans = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            long double w;
            cin >> w;
            w -= eps;
            if (i == j)
                continue;
            L[i][j] -= w / (1 - w);
            L[i][i] += w / (1 - w);
            if (i < j) {
                ans *= (1 - w);
            }
        }
    }
    L.n = n - 1;
    cout << ans * det(L);
    return 0;
}
// Asusetic eru quionours