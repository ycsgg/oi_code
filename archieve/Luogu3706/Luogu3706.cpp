#include <cmath>
#include <iostream>
using namespace std;
typedef unsigned long long ull;
const int N      = 305;
const ull base   = 19260817;
const double eps = 1e-8;
ull pw[N], H[N][N];
int n, m;
char s[N];
double eq[N][N];
ull getHash(int x, int l, int r) {
    return H[x][r] - H[x][l - 1] * pw[r - l + 1];
}
bool Eq0(double v) {
    return (v > -eps && v < eps);
}
void Solve(int n) {
    for (int i = 1; i <= n; i++) {
        if (Eq0(eq[i][i])) {
            for (int j = i + 1; j <= n; j++) {
                if (!Eq0(eq[j][i])) {
                    for (int k = i; k <= n + 1; k++) {
                        swap(eq[i][k], eq[j][k]);
                    }
                    break;
                }
            }
        }
        double t = 1.0 / eq[i][i];
        for (int j = i; j <= n + 1; j++) {
            eq[i][j] *= t;
        }
        for (int j = i + 1; j <= n; j++) {
            t = eq[j][i];
            for (int k = i; k <= n + 1; k++) {
                eq[j][k] -= eq[i][k] * t;
            }
        }
    }
    for (int i = n - 1; i >= 1; i--) {
        for (int j = i + 1; j <= n; j++) {
            eq[i][n + 1] -= eq[j][n + 1] * eq[i][j];
        }
    }
}
int main() {
    cin >> n >> m;
    pw[0] = 1;
    for (int i = 1; i <= m; i++) {
        pw[i] = pw[i - 1] * base;
    }
    for (int i = 1; i <= n; i++) {
        cin >> s + 1;
        for (int j = 1; j <= m; j++) {
            H[i][j] = H[i][j - 1] * base + (s[j] == 'H');
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= m; k++) {
                if (getHash(i, 1, k) == getHash(j, m - k + 1, m)) {
                    eq[i][j] += pow(2, k);
                }
            }
            eq[i][n + 1] = -1;
        }
    }
    for (int i = 1; i <= n; i++) {
        eq[n + 1][i] = 1;
    }
    eq[n + 1][n + 2] = 1;
    Solve(n + 1);
    for (int i = 1; i <= n; i++) {
        printf("%.8lf\n", eq[i][n + 2]);
    }
    return 0;
}
// Asusetic eru quionours
