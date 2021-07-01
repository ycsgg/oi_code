#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
using namespace std;
using ll    = long long;
const int N = 51, K = 201;
const ll INF = (1ll << 55);
struct Matrix {
    ll a[N * 5 + 1][N * 5 + 1];
    int siz;
    void identity() {
        for (int i = 1; i <= siz; i++) {
            for (int j = 1; j <= siz; j++) {
                a[i][j] = (i == j ? 0ll : -INF);
            }
        }
    }
    Matrix(int n) {
        for (int i = 1; i <= N * 5; i++) {
            for (int j = 1; j <= N * 5; j++) {
                a[i][j] = (-INF);
            }
        }
        siz = n;
    }
    Matrix() {
        for (int i = 1; i <= N * 5; i++) {
            for (int j = 1; j <= N * 5; j++) {
                a[i][j] = (-INF);
            }
        }
        siz = 0;
    }
    ll *operator[](const int &x) {
        return a[x];
    }
    const ll *operator[](const int &x) const {
        return a[x];
    }
    Matrix operator*(const Matrix &B) const {
        Matrix C;
        C.siz = siz;
        for (int i = 1; i <= siz; i++) {
            for (int j = 1; j <= siz; j++) {
                for (int k = 1; k <= siz; k++) {
                    C[i][j] = max(C[i][j], a[i][k] + B[k][j]);
                }
            }
        }
        return C;
    }
};
Matrix qpow(Matrix A, int b) {
    Matrix res(A.siz);
    res.identity();
    while (b) {
        if (b & 1) {
            res = res * A;
        }
        A = A * A;
        b /= 2;
    }
    return res;
}
int n, m, t, k;
int c[N], id[N][6];
int idcnt;
Matrix M, pre[30];
struct Fes {
    int t, x, y;
} fes[K];
void prePow() {
    pre[0] = M;
    for (int i = 1; i < 30; i++) {
        pre[i] = pre[i - 1] * pre[i - 1];
    }
}
void mul(Matrix &A, int p) {
    for (int bit = 0; bit < 30; ++bit) {
        if ((p >> bit) & 1) {
            Matrix res(A.siz);
            for (int j = 1; j <= A.siz; ++j) {
                for (int k = 1; k <= A.siz; ++k) {
                    if (A[1][k] == -INF || pre[bit][k][j] == -INF)
                        continue;
                    res[1][j] = max(A[1][k] + pre[bit][k][j], res[1][j]);
                }
            }
            A = res;
        }
    }
}
int main() {
    cin >> n >> m >> t >> k;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    M.siz = n * 5;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 5; j++) {
            id[i][j] = ++idcnt;
        }
        for (int j = 1; j < 5; j++) {
            M[id[i][j]][id[i][j + 1]] = 0;
        }
    }
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        M[id[u][w]][id[v][1]] = c[v];
    }
    prePow();

    for (int i = 1; i <= k; i++) {
        cin >> fes[i].t >> fes[i].x >> fes[i].y;
    }
    sort(fes + 1, fes + 1 + k, [&](const Fes &A, const Fes &B) -> bool {
        return A.t < B.t;
    });

    Matrix Q(n * 5);
    Q[1][id[1][1]] = c[1];

    int last = 0;
    for (int i = 1; i <= k; i++) {
        mul(Q, fes[i].t - last);
        if (Q[1][id[fes[i].x][1]] != -INF) {
            Q[1][id[fes[i].x][1]] += fes[i].y;
        }
        last = fes[i].t;
    }

    mul(Q, t - last);
    if (Q[1][id[1][1]] < 0) {
        cout << -1 << endl;
    } else {
        cout << Q[1][id[1][1]] << endl;
    }
}