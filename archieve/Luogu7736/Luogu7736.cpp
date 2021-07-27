#include <algorithm>
#include <array>
#include <assert.h>
#include <iostream>
#include <vector>
using namespace std;
using ll     = long long;
const ll mod = 998244353;
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
        // cout << "MUL" << endl;
        Matrix res(row, m.col);
        for (int k = 0; k < col; k++) {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < m.col; j++) {
                    res[i][j] += 1ll * (arr[i][k] * m[k][j]) % mod;
                    res[i][j] %= mod;
                }
            }
        }
        return res;
    }
};
ostream &operator<<(ostream &in, const Matrix &A) {
    for (int i = 0; i < A.col; i++) {
        cout << "{";
        for (int j = 0; j < A.row; j++) {
            if (j != A.row - 1) {
                cout << A[i][j] << ",";
            } else {
                cout << A[i][j];
            }
        }
        cout << "},";
        cout << endl;
    }
    return in;
}
int det(Matrix M, const ll p = 998244353l) {

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
int main() {
    int T;
    cin >> T;
    while (T--) {
        int k;
        cin >> k;
        vector<int> n(k + 1);
        for (int i = 1; i <= k; i++) {
            cin >> n[i];
        }
        vector<int> m(k);
        for (int i = 1; i < k; i++) {
            cin >> m[i];
        }
        Matrix::Matrix A(n[1], n[2]);
        for (int i = 1; i <= m[1]; i++) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            A[u][v] = 1;
        }
        for (int i = 2; i < k; i++) {
            Matrix::Matrix B(n[i], n[i + 1]);
            // cout << n[i] << " " << n[i + 1] << endl;
            for (int j = 1; j <= m[i]; j++) {
                int u, v;
                cin >> u >> v;
                --u;
                --v;
                // cout << u << " " << v << endl;
                B[u][v] = 1;
                // cout << "LK" << endl;
            }
            // cout << B << "B---------------" << endl;
            // cout << A << "A---------------" << endl;
            // cout << A * B << "A*B---------------" << endl;
            // cout << "END" << endl;
            A = A * B;
        }
        cout << Matrix::det(A) << endl;
    }
}