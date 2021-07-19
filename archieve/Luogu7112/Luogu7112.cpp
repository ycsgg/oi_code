#include <algorithm>
#include <array>
#include <assert.h>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
namespace Matrix {
struct Matrix {
    int row, col;
    vector<vector<ll>> arr;
    void init(int row, int col, int typ = 1) {
        this->row = row;
        this->col = col;
        arr       = vector<vector<ll>>(row, vector<ll>(col));
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (i == j && row == col) {
                    arr[i][j] = 1 * typ;
                } else {
                    arr[i][j] = 0;
                }
            }
        }
    }
    auto &operator[](int x) {
        return arr[x];
    }
    const auto &operator[](int x) const {
        return arr[x];
    }
    Matrix(int row = 2, int col = 2, int typ = 0) : row(row), col(col) {
        init(row, col, typ);
    }
    Matrix(const Matrix &m) {
        init(m.row, m.col);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                arr[i][j] = m[i][j];
            }
        }
    }
    Matrix operator*(const Matrix &m) const {
        Matrix res(row, m.col, 0);
        for (int k = 0; k < col; k++) {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < m.col; j++) {
                    res[i][j] += arr[i][k] * m[k][j];
                }
            }
        }
        return res;
    }
};
int det(Matrix M, const ll p = 998244353ll) {

    assert(M.col == M.row);

    int n   = M.col;
    ll sign = 1, res = 1;
    for (int i = 0; i < n; i++) {
        int k = i;
        for (int j = i; j < n; j++) {
            if (M[j][i]) {
                k = j;
                break;
            }
        }
        if (M[k][i] == 0) {
            return 0;
        }
        for (int j = k + 1; j < n; j++) {
            if (M[j][i] && M[j][i] < M[k][i]) {
                k = j;
            }
        }
        if (i != k) {
            swap(M[k], M[i]);
            sign = -sign;
        }
        for (int j = i + 1; j < n; j++) {
            if (M[j][i] > M[i][i]) {
                swap(M[j], M[i]);
                sign = -sign;
            }
            while (M[j][i]) {
                ll tmp = M[i][i] / M[j][i];
                for (int k = i; k < n; k++) {
                    M[i][k] = (M[i][k] - tmp * M[j][k] % p + p) % p;
                }
                swap(M[j], M[i]);
                sign = -sign;
            }
        }
        res = res * M[i][i] % p;
    }
    res = (res * sign + p) % p;
    return res;
}
} // namespace Matrix
ll n, p;
int main() {
    cin >> n >> p;
    Matrix::Matrix m(n, n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> m[i][j];
            m[i][j] %= p;
        }
    }
    cout << Matrix::det(m, p) << endl;
    return 0;
}
// Asusetic eru quionours
