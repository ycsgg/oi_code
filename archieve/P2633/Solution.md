### P2633 Count on a tree

https://www.luogu.com.cn/problem/P2633

树上差分一下然后发现就是一个区间静态在线第$k$大，码就好了

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e6;
int val[N], tmp[N];
int f[N][20], dep[N];
vector<int> G[N];
int head[N];
int cnt, tot_tmp;
struct Node {
    int lson, rson, sum;
} tr[10000005];
void build(Node &rt, int l, int r) {
    rt.sum = 0;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    rt.lson = ++cnt;
    build(tr[rt.lson], l, mid);
    rt.rson = ++cnt;
    build(tr[rt.rson], mid + 1, r);
}
void insert(Node &rt, Node pre, int l, int r, int p) {
    rt.sum = pre.sum + 1;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    if (p <= mid) {
        rt.lson = ++cnt;
        insert(tr[rt.lson], tr[pre.lson], l, mid, p);
        rt.rson = pre.rson;
    } else {
        rt.rson = ++cnt;
        insert(tr[rt.rson], tr[pre.rson], mid + 1, r, p);
        rt.lson = pre.lson;
    }
}
int find(int x) {
    return lower_bound(tmp + 1, tmp + 1 + tot_tmp, val[x]) - tmp;
}
void dfs(int x, int fa) {
    head[x] = ++cnt;
    insert(tr[head[x]], tr[head[fa]], 1, tot_tmp, find(x));
    f[x][0] = fa;
    dep[x]  = dep[fa] + 1;
    for (int i = 1; i <= 18; i++) {
        f[x][i] = f[f[x][i - 1]][i - 1];
    }
    for (auto v : G[x]) {
        if (v == fa)
            continue;
        dfs(v, x);
    }
}
int lca(int u, int v) {
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    for (int i = 18; i >= 0; i--) {
        if (dep[f[u][i]] >= dep[v]) {
            u = f[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = 18; i >= 0; i--) {
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }
    return f[u][0];
}
int query(Node x, Node y, Node z, Node w, int l, int r, int k) {
    if (l == r)
        return l;
    int sum = tr[x.lson].sum + tr[y.lson].sum - tr[z.lson].sum - tr[w.lson].sum;
    int mid = (l + r) >> 1;
    if (sum >= k)
        return query(tr[x.lson], tr[y.lson], tr[z.lson], tr[w.lson], l, mid, k);
    return query(tr[x.rson], tr[y.rson], tr[z.rson], tr[w.rson], mid + 1, r,
                 k - sum);
}
int querypath(int u, int v, int k) {
    int Lca = lca(u, v);
    return tmp[query(tr[head[u]], tr[head[v]], tr[head[Lca]],
                     tr[head[f[Lca][0]]], 1, tot_tmp, k)];
}
int n, m;
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
        tmp[i] = val[i];
    }
    sort(tmp + 1, tmp + 1 + n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    tot_tmp = unique(tmp + 1, tmp + 1 + n) - tmp - 1;
    head[0] = 1;
    build(tr[1], 1, tot_tmp);
    dfs(1, 0);
    int lastans = 0;
    for (int i = 1; i <= m; i++) {
        int u, v, k;
        cin >> u >> v >> k;
        int nowans = querypath(u ^ lastans, v, k);
        cout << nowans << endl;
        lastans = nowans;
    }
}
```

