#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 3e5 + 10;
const int INF = 0x3f3f3f3f;
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
} G, Tr;
int dep[N];
int f[N], g[N];
int tot;
int n, m;
bool mark[N];
void dfs(int x, int mid) {
    f[x] = -INF;
    g[x] = INF;
    for (auto v : Tr.edge[x]) {
        dfs(v, mid);
        f[x] = max(f[x], f[v] + 1);
        g[x] = min(g[x], g[v] + 1);
    }
    if (f[x] + g[x] <= mid) {
        f[x] = -INF;
    }
    if (g[x] > mid && mark[x]) {
        f[x] = max(f[x], 0);
    }
    if (f[x] == mid) {
        f[x] = -INF;
        g[x] = 0;
        tot++;
    }
}
bool check(int x) {
    tot = 0;
    dfs(1, x);
    if (f[1] >= 0) {
        ++tot;
    }
    return tot <= m;
}
void pre_dfs(int x, int fa) {
    for (auto v : G.edge[x]) {
        if (v != fa) {
            Tr.add(x, v);
            pre_dfs(v, x);
        }
    }
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> mark[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        G.add(u, v);
        G.add(v, u);
    }
    pre_dfs(1, 0);
    int l = 0, r = n, res = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << res;
    return 0;
}
// Asusetic eru quionours.