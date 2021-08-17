#include <array>
#include <assert.h>
#include <iostream>
#include <vector>
using namespace std;
namespace Matrix {
using ll = long long;
constexpr ll mod = 1e9 + 7;
template <typename T>
struct Matrix {
    int row, col;
    // vector<vector<T>> arr;
    T arr[75][75];
    void init(int row, int col, int typ = 1) {
        this->row = row;
        this->col = col;
        // arr = vector<vector<T>>(row, vector<T>(col, T()));
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
template <typename T>
ostream &operator<<(ostream &in, const Matrix<T> &A) {
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
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b /= 2;
    }
    return res;
}
template <typename T>
T det(Matrix<T> M, const ll p = mod) {

    assert(M.col == M.row);

    int n = M.col;
    ll ans = 1;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++)
            if ((M[i][i]) && M[j][i]) {
                ans = p - ans;
                swap(M[i], M[j]);
                break;
            }
        if (!M[i][i])
            return 0;
        ll t = qpow(M[i][i], p - 2);
        for (int j = i + 1; j < n; j++) {
            ll t2 = t * M[j][i] % p;
            for (int k = i; k < n; k++) {
                M[j][k] = (M[j][k] - t2 * M[i][k] % p + p) % p;
            }
        }
    }
    for (int i = 1; i < n; i++) {
        ans *= M[i][i];
        ans %= p;
    }
    return ans;
}
} // namespace Matrix
namespace Transform {
using Poly = vector<int>;
const int mod = 1e9 + 7;
const int inv2 = 500000004;
int getLen(int x) {
    int L = 1;
    while (L < x) {
        L *= 2;
    }
    return L;
}
void unit_OR(Poly &f, int lim, int mid, int typ) {
    for (int i = 0; i < lim; i += mid * 2) {
        for (int j = 0; j < mid; j++) {
            auto x = f[i + j], y = f[i + j + mid];
            if (typ == 1) {
                f[i + j + mid] = (1ll * y + x) % mod;
            } else {
                f[i + j + mid] = (1ll * y - x + mod) % mod;
            }
        }
    }
}
void unit_AND(Poly &f, int lim, int mid, int typ) {
    for (int i = 0; i < lim; i += mid * 2) {
        for (int j = 0; j < mid; j++) {
            auto x = f[i + j], y = f[i + j + mid];
            if (typ == 1) {
                f[i + j] = (1ll * x + y) % mod;
            } else {
                f[i + j] = (1ll * x - y + mod) % mod;
            }
        }
    }
}
void unit_XOR(Poly &f, int lim, int mid, int typ) {
    for (int i = 0; i < lim; i += mid * 2) {
        for (int j = 0; j < mid; j++) {
            auto x = f[i + j], y = f[i + j + mid];
            f[i + j] = (x + y) % mod;
            f[i + j + mid] = (x - y + mod) % mod;
            if (typ == -1) {
                f[i + j] = 1ll * f[i + j] * inv2 % mod;
                f[i + j + mid] = 1ll * f[i + j + mid] * inv2 % mod;
            }
        }
    }
}
void exFWT(Poly &f, int typ, const string &oper) {
    int lim = getLen(f.size());
    f.resize(lim);
    for (int mid = 1, cur = 0; mid < lim; mid *= 2, cur++) {
        if (oper[cur] == '|') {
            unit_OR(f, lim, mid, typ);
        } else if (oper[cur] == '&') {
            unit_AND(f, lim, mid, typ);
        } else {
            unit_XOR(f, lim, mid, typ);
        }
    }
}
} // namespace Transform
using namespace Transform;
int n, m;
string s;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    cin >> s;
    int w = s.length();
    Matrix::Matrix<Poly> M(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            M[i][j].resize(1 << w);
        }
    }
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        M[u][v][w]--;
        M[v][u][w]--;
        M[u][u][w]++;
        M[v][v][w]++;
    }
    n--;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < (1 << w); k++) {
                if (M[i][j][k] < 0) {
                    M[i][j][k] += mod;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < (1 << w); k++) {
                if (M[i][j][k] < 0) {
                    M[i][j][k] += mod;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            exFWT(M[i][j], 1, s);
        }
    }
    vector<int> c(1 << w);
    for (int t = 0; t < (1 << w); t++) {
        Matrix::Matrix<int> tmp(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                tmp[i][j] = M[i][j][t];
            }
        }
        c[t] = Matrix::det(tmp);
    }
    exFWT(c, -1, s);
    for (int i = (1 << w) - 1; ~i; i--) {
        if (c[i]) {
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    cout.flush();
    return 0;
}
// Asusetic eru quionours