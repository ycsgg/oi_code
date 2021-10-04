#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 305;
const double eps = 1e-6;
int n;
struct Matrix {
    double a[N][N];
    double *operator[](int x) {
        return a[x];
    }
    const double *operator[](int x) const {
        return a[x];
    }
    /*Matrix operator*(const Matrix &b) {
        Matrix res;
        memset(res.a, 0, sizeof(res.a));
        for (int i = 1; i <= n; i++) {
            for (int k = 1; k <= n; k++) {
                for (int j = 1; j <= n; j++) {
                    res[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return res;
    }*/
} A, B, C;
// A^-1B
void InvMul(const Matrix &_A, const Matrix &B, Matrix &res) {
    auto A = _A;
    for (int i = 1; i <= n; i++) {
        auto mx = i;
        for (int j = i + 1; j <= n; j++) {
            if (abs(A[j][i]) > abs(A[mx][i])) {
                mx = j;
            }
        }
        if (abs(A[mx][i]) <= eps) {
            cout << "NIE";
            exit(0);
        }
        if (mx != i) {
            for (int j = 1; j <= n; j++) {
                swap(A[i][j], A[mx][j]);
                swap(res[i][j], res[mx][j]);
            }
        }
        auto t = A[i][i];
        for (int j = 1; j <= n; j++) {
            A[i][j] /= t;
            res[i][j] /= t;
        }
        for (int j = 1; j <= n; j++) {
            if (j != i) {
                auto t = A[j][i];
                for (int k = 1; k <= n; k++) {
                    A[j][k] -= A[i][k] * t;
                    res[j][k] -= res[i][k] * t;
                }
            }
        }
    }
}
bool vis[N];
int link[N];
bool judge(int x) {
    for (int i = 1; i <= n; i++) {
        if (abs(C[x][i]) > eps && !vis[i]) {
            vis[i] = 1;
            if (!link[i] || judge(link[i])) {
                link[i] = x;
                return true;
            }
        }
    }
    return false;
}
int match(int x, int p) {
    for (int i = 1; i <= n; i++) {
        if (abs(C[x][i]) > eps && !vis[i]) {
            vis[i] = 1;
            if (link[i] == p || (link[i] > p && match(link[i], p))) {
                link[i] = x;
                return i;
            }
        }
    }
    return 0;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> A[j][i];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> B[j][i];
            C[j][i] = B[j][i];
        }
    }
    InvMul(A, B, C);
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        if (!match(i, 0)) {
            cout << "NIE";
            return 0;
        }
    }
    cout << "TAK\n";
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        cout << match(i, i) << '\n';
    }
    return 0;
}
// Asusetic eru quionours.