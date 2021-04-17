#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
int n, m, c;
const int N = 2e5 + 10;
int p[N], id[N], w[N];
struct Edge {
    int v;
    int nxt;
} edge[N * 2];
int head[N], ecnt;
int lca[N];
void add(int u, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
int fa[N][21], dep[N];
void pre(int x,int f) {
    fa[x][0] = f;
    dep[x]   = dep[f] + 1;
    for (int i = 1; i <= 19; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == f) {
            continue;
        }
        pre(v, x);
    }
}
int getLCA(int u, int v) {
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    for (int i = 19; i >= 0; i--) {
        if (dep[fa[u][i]] >= dep[v]) {
            u = fa[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = 19; i >= 0; i--) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}
vector<int> up[N], down[N];
int updep[N][21], ans[N];
int last[N];
void qup(int x) {
    int p            = last[w[x]];
    last[w[x]]       = dep[x];
    updep[dep[x]][0] = last[w[x] + 1];
    for (int i = 1; i <= 19; i++) {
        updep[dep[x]][i] = updep[updep[dep[x]][i - 1]][i - 1];
    }
    for (auto d : up[x]) {
        int x = last[1];
        if (x < dep[lca[d]]) {
            continue;
        }
        ++ans[d];
        for (int i = 19; i >= 0; i--) {
            if (updep[x][i] >= dep[lca[d]]) {
                ans[d] += (1 << i);
                x = updep[x][i];
            }
        }
    }
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v != fa[x][0]) {
            qup(v);
        }
    }
    last[w[x]] = p;
}
void qdown(int x) {
    int p            = last[w[x]];
    last[w[x]]       = dep[x];
    updep[dep[x]][0] = last[w[x] - 1];
    for (int i = 1; i <= 19; i++) {
        updep[dep[x]][i] = updep[updep[dep[x]][i - 1]][i - 1];
    }
    for (auto d : down[x]) {
        int l = ans[d] + 1, r = c, res = ans[d];
        while (l <= r) {
            int mid = (l + r) / 2;
            int x = last[mid], cnt = mid - ans[d] - 1;
            for (int i = 19; i >= 0; i--) {
                if ((1 << i) & cnt) {
                    x = updep[x][i];
                }
            }
            if (x > dep[lca[d]]) {
                res = mid;
                l   = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        ans[d] = res;
    }
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v != fa[x][0]) {
            qdown(v);
        }
    }
    last[w[x]] = p;
}
int main() {
    cin >> n >> m >> c;
    for (int i = 1; i <= c; i++) {
        cin >> p[i];
        id[p[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        w[i] = id[w[i]];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    dep[1] = 1;
    pre(1, 0);
    int q;
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int u, v;
        cin >> u >> v;
        lca[i] = getLCA(u, v);
        up[u].push_back(i);
        down[v].push_back(i);
    }
    memset(updep, 0, sizeof(updep));
    qup(1);
    qdown(1);
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}