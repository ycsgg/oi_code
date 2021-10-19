#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
struct Graph {
    vector<int> edge[N];
    void add(int x, int v) {
        edge[x].emplace_back(v);
    }
} Tr;
int n, V;
ll p[N], s[N], ans;
ll f[N][101], g[N][101];
void dfs(int x, int _fa) {
    for (int i = 1; i <= V; i++) {
        f[x][i] = s[x];
        g[x][i] = s[x] - p[_fa];
    }
    for (auto v : Tr.edge[x]) {
        if (v == _fa) {
            continue;
        }
        dfs(v, x);
        for (int j = 0; j <= V; ++j) {
            ans = max(ans, f[x][j] + g[v][V - j]);
        }
        for (int j = 1; j <= V; ++j) {
            f[x][j] = max(f[x][j], max(f[v][j], f[v][j - 1] + s[x] - p[v]));
            g[x][j] = max(g[x][j], max(g[v][j], g[v][j - 1] + s[x] - p[_fa]));
        }
    }
    //
    for (int i = 1; i <= V; i++) {
        f[x][i] = s[x];
        g[x][i] = s[x] - p[_fa];
    }
    vector<int> son;
    son.reserve(Tr.edge[x].size());
    for (auto v : Tr.edge[x]) {
        if (v == _fa) {
            continue;
        }
        son.push_back(v);
    }
    reverse(son.begin(), son.end());
    for (auto v : son) {
        for (int j = 0; j <= V; ++j) {
            ans = max(ans, f[x][j] + g[v][V - j]);
        }
        for (int j = 1; j <= V; ++j) {
            f[x][j] = max(f[x][j], max(f[v][j], f[v][j - 1] + s[x] - p[v]));
            g[x][j] = max(g[x][j], max(g[v][j], g[v][j - 1] + s[x] - p[_fa]));
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> V;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for (int i = 1; i < n; i++) {
        int x, v;
        cin >> x >> v;
        Tr.add(x, v);
        Tr.add(v, x);
        s[x] += p[v];
        s[v] += p[x];
    }
    dfs(1, 0);
    cout << ans;
    return 0;
}
// Asusetic eru quionours.
