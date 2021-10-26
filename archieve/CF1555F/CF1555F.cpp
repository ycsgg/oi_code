#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 5e5 + 10;
struct Graph {
    struct Node {
        int v, w;
    };
    vector<Node> edge[N];
    void add(int u, int v, int w) {
        edge[u].emplace_back(Node{v, w});
    }
} Tr;
namespace DSU {
int fa[N];
void init(int x) {
    for (int i = 1; i <= x; i++) {
        fa[i] = i;
    }
}
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        fa[x] = y;
    }
}
} // namespace DSU
int n, q;
struct Oper {
    int u, v, x;
} a[N];
int ans[N];
namespace BIT {
int c[N];
int lowbit(int x) {
    return x & (-x);
}
void add(int pos, int v) {
    while (pos <= n) {
        c[pos] += v;
        pos += lowbit(pos);
    }
}
int query(int pos) {
    int res = 0;
    while (pos) {
        res += c[pos];
        pos -= lowbit(pos);
    }
    return res;
}
} // namespace BIT
int dfn[N], tim;
int pre[N], siz[N];
int fa[20][N], dep[N];
void dfs(int x, int _fa) {
    dep[x] = dep[_fa] + 1;
    dfn[x] = ++tim;
    fa[0][x] = _fa;
    for (int i = 1; i <= 19; i++) {
        fa[i][x] = fa[i - 1][fa[i - 1][x]];
    }
    for (auto e : Tr.edge[x]) {
        auto v = e.v;
        auto w = e.w;
        if (v == _fa) {
            continue;
        }
        pre[v] = pre[x] ^ w;
        dfs(v, x);
        siz[x] += siz[v];
    }
    siz[x]++;
}
int LCA(int x, int y) {
    if (dep[x] < dep[y]) {
        swap(x, y);
    }
    int d = dep[x] - dep[y];
    for (int i = 19; ~i; i--) {
        if (d & (1 << i)) {
            x = fa[i][x];
        }
    }
    if (x == y) {
        return x;
    }
    for (int i = 19; ~i; i--) {
        if (fa[i][x] != fa[i][y]) {
            x = fa[i][x];
            y = fa[i][y];
        }
    }
    return fa[0][x];
}
int main() {
    cin >> n >> q;
    DSU::init(n);
    for (int i = 1; i <= q; i++) {
        cin >> a[i].u >> a[i].v >> a[i].x;
        if (DSU::find(a[i].u) != DSU::find(a[i].v)) {
            Tr.add(a[i].u, a[i].v, a[i].x);
            Tr.add(a[i].v, a[i].u, a[i].x);
            DSU::merge(a[i].u, a[i].v);
            ans[i] = 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            dfs(i, 0);
        }
    }
    for (int i = 1; i <= q; i++) {
        if (ans[i]) {
            continue;
        }
        auto u = a[i].u;
        auto v = a[i].v;
        int lca = LCA(u, v);
        if (((pre[u] ^ pre[v] ^ a[i].x) == 1)) {
            auto x1 = BIT::query(dfn[u]) - BIT::query(dfn[lca]);
            auto x2 = BIT::query(dfn[v]) - BIT::query(dfn[lca]);
            if (x1 || x2) {
                continue;
            }
            ans[i] = 1;
            while (u != lca) {
                BIT::add(dfn[u], 1);
                BIT::add(dfn[u] + siz[u], -1);
                u = fa[0][u];
            }
            while (v != lca) {
                BIT::add(dfn[v], 1);
                BIT::add(dfn[v] + siz[v], -1);
                v = fa[0][v];
            }
        }
    }
    for (int i = 1; i <= q; i++) {
        if (ans[i]) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}
// Asusetic eru quionours.