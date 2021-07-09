#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 10;
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
} Tr;
int n, m, k;
int f[N][21], g[N][21];
// f[x][k]:=x子树距离为k的需要灭火器的点数
// g[x][k]:=x子树距离为k的额外灭火器
int ans;
void dfs(int x, int fa) {
    for (auto v : Tr.edge[x]) {
        if (v == fa)
            continue;
        dfs(v, x);
        for (int j = 1; j <= k; j++) {
            f[x][j] = min(f[x][j] + f[v][j - 1], n); //! can't beyond n !
            g[x][j] += g[v][j - 1];
        }
    }
    g[x][0]++;
    if (g[x][k]) {
        int t   = ceil(1.0 * g[x][k] / m);
        f[x][0] = min(t * m, n);
        ans += t;
    }
    for (int i = 0; i <= k; i++) {
        int d = min(f[x][i], g[x][k - i]);
        f[x][i] -= d;
        g[x][k - i] -= d;
    }
    for (int i = 0; i < k; i++) {
        int d = min(f[x][i], g[x][k - i - 1]);
        f[x][i] -= d;
        g[x][k - i - 1] -= d;
    }
}
int main() {
    cin >> n >> m >> k;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        Tr.add(u, v);
        Tr.add(v, u);
    }
    dfs(1, 0);
    for (int i = 0; i <= k; i++) {
        for (int j = k - i; j >= 0; j--) {
            int d = min(f[1][i], g[1][j]);
            f[1][i] -= d;
            g[1][j] -= d;
        }
    }
    int tot = 0;
    for (int i = 0; i <= k; i++) {
        tot += g[1][i];
    }
    ans += ceil(1.0 * tot / m);
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours