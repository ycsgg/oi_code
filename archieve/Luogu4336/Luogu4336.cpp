#include <algorithm>
#include <array>
#include <assert.h>
#include <iostream>
#include <vector>
using namespace std;
using ll     = long long;
const ll mod = 1e9 + 7;
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
    Matrix(int row, int col) : row(row), col(col) {
        init(row, col, 0);
    }
    Matrix(int n = 2) {
        col = row = n;
        init(n, n, 0);
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
        Matrix res(row, m.col);
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
int det(Matrix M, const ll p = 1000000007ll) {

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
const int N = 22;
int n;
ll MatrixTree(const Matrix::Matrix &G) {
    Matrix::Matrix D(G.row), L(G.row - 1);
    for (int i = 0; i < n; i++) {
        D[i][i] = 0;
        for (int j = 0; j < n; j++) {
            D[i][i] += G[j][i];
        }
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            L[i][j] = (D[i][j] - G[i][j] + mod) % mod;
        }
    }
    return Matrix::det(L);
}
int u[N][N * N], v[N][N * N], m[N];
int main() {
    cin >> n;
    Matrix::Matrix G(n);
    for (int i = 1; i < n; i++) {
        cin >> m[i];
        for (int j = 1; j <= m[i]; j++) {
            cin >> u[i][j] >> v[i][j];
            --u[i][j];
            --v[i][j];
            G[u[i][j]][v[i][j]]++;
            G[v[i][j]][u[i][j]]++;
        }
    }
    ll ans = 0;
    for (int S = 0; S < (1 << (n - 1)); S++) {
        int sign = 1;
        for (int i = 1; i < n; i++) {
            if (S & (1 << i - 1)) {
                for (int j = 1; j <= m[i]; j++) {
                    G[u[i][j]][v[i][j]]--;
                    G[v[i][j]][u[i][j]]--;
                }
                sign = -sign;
            }
        }
        ans = (ans + (1ll * sign * MatrixTree(G) + mod) % mod) % mod;
        for (int i = 1; i < n; i++) {
            if (S & (1 << i - 1)) {
                for (int j = 1; j <= m[i]; j++) {
                    G[u[i][j]][v[i][j]]++;
                    G[v[i][j]][u[i][j]]++;
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours