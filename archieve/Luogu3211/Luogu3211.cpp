#include <array>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
const double eps = 1e-6;
const int N      = 105;
int n, m;
int mmax = -1;
array<int, N> deg;
struct Graph {
    struct Node {
        int v, w;
    };
    vector<Node> edge[N];
    void add(int u, int v, int w) {
        edge[u].emplace_back(Node{v, w});
    }
} G;
vector<vector<double>> buildEq(int pos) {
    vector<vector<double>> Eq(n + 2, vector<double>(n + 2));
    Eq[n][n] = 1;
    for (int i = 1; i < n; i++) {
        Eq[i][i] = deg[i];
        for (auto e : G.edge[i]) {
            if (e.w & (1 << pos)) {
                Eq[i][e.v] += 1;
                Eq[i][n + 1] += 1;
            } else {
                Eq[i][e.v] -= 1;
            }
        }
    }
    return Eq;
}
bool Eq0(double v) {
    return (v > -eps && v < eps);
}
vector<vector<double>> Gauss(vector<vector<double>> &Eq) {
    for (int i = 1; i <= n; i++) {
        if (Eq0(Eq[i][i])) {
            for (int j = i + 1; j <= n; j++) {
                if (!Eq0(Eq[j][i])) {
                    for (int k = i; k <= n + 1; k++) {
                        swap(Eq[i][k], Eq[j][k]);
                    }
                    break;
                }
            }
        }
        double t = 1.0 / Eq[i][i];
        for (int j = i; j <= n + 1; j++) {
            Eq[i][j] *= t;
        }
        for (int j = i + 1; j <= n; j++) {
            t = Eq[j][i];
            for (int k = i; k <= n + 1; k++) {
                Eq[j][k] -= Eq[i][k] * t;
            }
        }
    }
    for (int i = n - 1; i >= 1; i--) {
        for (int j = i + 1; j <= n; j++) {
            Eq[i][n + 1] -= Eq[j][n + 1] * Eq[i][j];
        }
    }
    return Eq;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G.add(u, v, w);
        if (u != v) {
            G.add(v, u, w);
            ++deg[v];
        }
        ++deg[u];
        mmax = max(mmax, w);
    }
    double ans = 0;
    for (int i = 0; (1 << i) <= mmax; i++) {
        auto &&Eq = buildEq(i);
        ans += Gauss(Eq)[1][n + 1] * (1 << i);
    }
    printf("%.3lf", ans);
    return 0;
}
// Asusetic eru quionours