#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N = 8e4 + 10;
int a[N], b[N];
namespace SegmentTree {
struct Node {
    int ls, rs, v;
};
array<Node, N * 108> tr;
array<int, N> rt;
int tot;
void insert(int &rt, int pre, int l, int r, int pos) {
    rt     = ++tot;
    tr[rt] = tr[pre];
    tr[rt].v++;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        insert(tr[rt].ls, tr[pre].ls, l, mid, pos);
    } else {
        insert(tr[rt].rs, tr[pre].rs, mid + 1, r, pos);
    }
}
int query(int u, int v, int x, int y, int l, int r, int k) {
    if (l == r) {
        return a[l];
    }
    int sum = tr[tr[u].ls].v + tr[tr[v].ls].v - tr[tr[x].ls].v - tr[tr[y].ls].v;
    int mid = (l + r) / 2;
    if (k <= sum) {
        return query(tr[u].ls, tr[v].ls, tr[x].ls, tr[y].ls, l, mid, k);
    } else {
        return query(tr[u].rs, tr[v].rs, tr[x].rs, tr[y].rs, mid + 1, r,
                     k - sum);
    }
}
} // namespace SegmentTree
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
} G;
int n, m, t;
array<int, N> root, dep, siz;
int fa[N][20];
int cnt;
void dfs(int u, int _fa, int rt) {
    SegmentTree::insert(SegmentTree::rt[u], SegmentTree::rt[_fa], 1, cnt, b[u]);
    dep[u]   = dep[_fa] + 1;
    fa[u][0] = _fa;
    siz[rt]++;
    root[u] = rt;
    for (int i = 1; i <= 18; i++) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }
    for (auto v : G.edge[u]) {
        if (v != rt && v != _fa) {
            dfs(v, u, rt);
        }
    }
    return;
}
int get_LCA(int u, int v) {
    if (dep[u] > dep[v]) {
        swap(u, v);
    }
    for (int i = 18; ~i; i--) {
        if (dep[fa[v][i]] >= dep[u]) {
            v = fa[v][i];
        }
    }
    if (u == v)
        return u;
    for (int i = 18; ~i; i--) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}
int main() {
    int tmp;
    cin >> tmp >> n >> m >> t;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i]    = a[i];
        root[i] = i;
    }
    sort(a + 1, a + 1 + n);
    cnt = unique(a + 1, a + 1 + n) - a - 1;
    for (int i = 1; i <= n; i++) {
        b[i] = lower_bound(a + 1, a + 1 + cnt, b[i]) - a;
    }
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        G.add(x, y);
        G.add(y, x);
    }
    for (int i = 1; i <= n; i++) {
        if (root[i] == i) {
            dfs(i, 0, i);
        }
    }
    int lastans = 0;
    while (t--) {
        char opt;
        int x, y, p;
        cin >> opt;
        cin >> x >> y;
        x ^= lastans;
        y ^= lastans;
        if (opt == 'Q') {
            cin >> p;
            p ^= lastans;
            int lca  = get_LCA(x, y);
            int plca = fa[lca][0];
            using SegmentTree::rt;
            lastans =
                SegmentTree::query(rt[x], rt[y], rt[lca], rt[plca], 1, cnt, p);
            cout << lastans << endl;
        } else {
            G.add(x, y);
            G.add(y, x);
            int fx = root[x];
            int fy = root[y];
            if (siz[fy] < siz[fx]) {
                swap(fy, fx);
                swap(x, y);
            }
            dfs(x, y, fy);
        }
    }
    return 0;
}
// Asusetic eru quionours