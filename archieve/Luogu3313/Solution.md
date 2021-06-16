### P3313 [SDOI2014]旅行

常规题目，每个宗教开一个线段树动态开点即可

```cpp
#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 5;
int n, q;
namespace SegmentTree {
struct Node {
    int mmax, sum;
    int ls, rs;
};
array<Node, N * 30> mem;
int tot_used = 0;
struct SegmentTree {
    int root;
    array<Node, N * 30> &tr;
    SegmentTree() : root(0) ,tr(mem){
    }
    void pushup(int x) {
        tr[x].sum  = tr[tr[x].ls].sum + tr[tr[x].rs].sum;
        tr[x].mmax = max(tr[tr[x].ls].mmax, tr[tr[x].rs].mmax);
    }
    void update(int &rt, int l, int r, int pos, int v) {
        if (!rt) {
            rt = ++tot_used;
        }
        tr[rt].mmax = max(tr[rt].mmax, v);
        tr[rt].sum += v;
        if (l == r) {
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) {
            update(tr[rt].ls, l, mid, pos, v);
        } else {
            update(tr[rt].rs, mid + 1, r, pos, v);
        }
    }
    void update(int pos, int v) {
        update(root, 1, n, pos, v);
    }
    void remove(int &rt, int l, int r, int pos) {
        if (l == r) {
            tr[rt].sum = tr[rt].mmax = 0;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) {
            remove(tr[rt].ls, l, mid, pos);
        } else {
            remove(tr[rt].rs, mid + 1, r, pos);
        }
        pushup(rt);
    }
    void remove(int pos) {
        remove(root, 1, n, pos);
    }
    int query_sum(int rt, int l, int r, int L, int R) {
        if (R >= r && L <= l) {
            return tr[rt].sum;
        }
        int mid = (l + r) / 2;
        int sum = 0;
        if (L <= mid) {
            sum += query_sum(tr[rt].ls, l, mid, L, R);
        }
        if (mid < R) {
            sum += query_sum(tr[rt].rs, mid + 1, r, L, R);
        }
        return sum;
    }
    int query_max(int rt, int l, int r, int L, int R) {
        if (R >= r && L <= l) {
            return tr[rt].mmax;
        }
        int mid  = (l + r) / 2;
        int mmax = -1;
        if (L <= mid) {
            mmax = max(mmax, query_max(tr[rt].ls, l, mid, L, R));
        }
        if (mid < R) {
            mmax = max(mmax, query_max(tr[rt].rs, mid + 1, r, L, R));
        }
        return mmax;
    }
    int query_sum(int l, int r) {
        return query_sum(root, 1, n, l, r);
    }
    int query_max(int l, int r) {
        return query_max(root, 1, n, l, r);
    }
};
} // namespace SegmentTree
SegmentTree::SegmentTree Tr[N];
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
} G;
array<int, N> fa, dep, siz, id, son, top, pos;
int tim;
void dfs1(int x, int _fa) {
    fa[x]  = _fa;
    dep[x] = dep[_fa] + 1;
    siz[x] = 1;
    for (auto v : G.edge[x]) {
        if (v == _fa) {
            continue;
        }
        dfs1(v, x);
        siz[x] += siz[v];
        if (siz[v] > siz[son[x]]) {
            son[x] = v;
        }
    }
}
void dfs2(int x, int topf) {
    top[x]  = topf;
    pos[x]  = ++tim;
    id[tim] = x;
    if (!son[x]) {
        return;
    }
    dfs2(son[x], topf);
    for (auto v : G.edge[x]) {
        if (v == son[x] || v == fa[x])
            continue;
        dfs2(v, v);
    }
}
int Tr_Sum(int c, int u, int v) {
    auto &Tree = Tr[c];
    int ans    = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        ans = ans + Tree.query_sum(pos[top[u]], pos[u]);
        u   = fa[top[u]];
    }
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    ans = ans + Tree.query_sum(pos[v], pos[u]);
    return ans;
}
int Tr_Max(int c, int u, int v) {
    auto &Tree = Tr[c];
    int ans    = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        ans = max(ans, Tree.query_max(pos[top[u]], pos[u]));
        u   = fa[top[u]];
    }
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    ans = max(ans, Tree.query_max(pos[v], pos[u]));
    return ans;
}
array<int, N> w, c;
int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> c[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        G.add(u, v);
        G.add(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1; i <= n; i++) {
        Tr[c[i]].update(pos[i], w[i]);
    }
    while (q--) {
        char opt[8];
        int x, y;
        cin >> opt >> x >> y;
        if (opt[0] == 'C') {
            Tr[c[x]].remove(pos[x]);
            if (opt[1] == 'C') {
                Tr[y].update(pos[x], w[x]);
                c[x] = y;
            } else {
                Tr[c[x]].update(pos[x], y);
                w[x] = y;
            }
        } else {
            if (opt[1] == 'S') {
                cout << Tr_Sum(c[x], x, y) << endl;
            } else {
                cout << Tr_Max(c[x], x, y) << endl;
            }
        }
    }
    return 0;
}
// Asusetic eru quionours
```

