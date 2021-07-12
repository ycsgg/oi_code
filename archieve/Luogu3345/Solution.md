### P3345 [ZJOI2015]幻想乡战略游戏

点分树题，考虑不用点分树做

我们先钦点最大的子树最小的点作为答案，考虑其他的点作为决策点时向重心移动一条边 $e$ ，两边端点为 $x,y$ 方向为 $x \rightarrow y$

则答案变化为 $-e\times siz_x+e\times siz_y$

因为这个点不是重心，所以 $siz_y < siz_x$ 所以答案更优了

所以按照普通的树的重心，只要找到满足 $2siz_x \ge siz_{root}$ 的最深的点即使重心

线段树叶子维护子树大小和最大值线段树上二分即可找到

答案为 $\sum dis(x,y) \times w(y)=\sum dis(x,root)\times w(y)+\sum dis(y,root)\times w(y)-2\sum dis(lca,root) \times w(y)$

前两个可以直接维护，后面的考虑 $lca \rightarrow root$ 的路径其实是两个点到根路径的交

考虑按贡献查询

每次修改点值直接把她到根全加上，然后查询 $siz_x\times (dis_x-dis_{fa_x})$

```cpp
#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 10;
#define int ll
using ll    = long long;
struct Graph {
    struct Node {
        int v, w;
    };
    vector<Node> edge[N];
    void add(int u, int v, int w) {
        edge[u].emplace_back(Node{v, w});
    }
} Tr;
array<int, N> fa, son, siz, dep, dis, top;
void dfs1(int x, int f) {
    fa[x]  = f;
    dep[x] = dep[f] + 1;
    siz[x] = 1;
    for (auto e : Tr.edge[x]) {
        int v = e.v;
        if (v == f)
            continue;
        dis[v] = dis[x] + e.w;
        dfs1(v, x);
        siz[x] += siz[v];
        if (siz[son[x]] < siz[v]) {
            son[x] = v;
        }
    }
}
array<int, N> id, pos, w;
int tot;
void dfs2(int x, int topf) {
    top[x]   = topf;
    id[x]    = ++tot;
    pos[tot] = x;
    w[tot]     = dis[x] - dis[fa[x]];
    if (!son[x])
        return;
    dfs2(son[x], topf);
    for (auto e : Tr.edge[x]) {
        if (e.v != fa[x] && e.v != son[x]) {
            dfs2(e.v, e.v);
        }
    }
}
namespace SegmentTree {
#define ls(x) (x * 2)
#define rs(x) (x * 2 + 1)
struct Node {
    ll val, sum, tag, siz;
    int l, r;
} tr[N << 2];
void pushup(int rt) {
    tr[rt].val = tr[ls(rt)].val + tr[rs(rt)].val;
    tr[rt].sum = tr[ls(rt)].sum + tr[rs(rt)].sum;
    tr[rt].siz = max(tr[ls(rt)].siz, tr[rs(rt)].siz);
}
void pushdown(int rt) {
    if (tr[rt].tag) {
        tr[ls(rt)].siz += tr[rt].tag;
        tr[rs(rt)].siz += tr[rt].tag;
        tr[ls(rt)].tag += tr[rt].tag;
        tr[rs(rt)].tag += tr[rt].tag;
        tr[ls(rt)].sum += tr[rt].tag * tr[ls(rt)].val;
        tr[rs(rt)].sum += tr[rt].tag * tr[rs(rt)].val;
        tr[rt].tag = 0;
    }
}
void build(int rt, int l, int r) {
    tr[rt].l = l;
    tr[rt].r = r;
    if (l == r) {
        tr[rt].val = w[l];
        tr[rt].siz = 0;
        tr[rt].sum = 0;
        return;
    }
    int mid = (l + r) / 2;
    build(ls(rt), l, mid);
    build(rs(rt), mid + 1, r);
    pushup(rt);
}
void update(int rt, int L, int R, ll v) {
    auto &l = tr[rt].l;
    auto &r = tr[rt].r;
    if (l >= L && r <= R) {
        tr[rt].tag += v;
        tr[rt].sum += v * tr[rt].val;
        tr[rt].siz += v;
        return;
    }
    pushdown(rt);
    int mid = (l + r) / 2;
    if (L <= mid) {
        update(ls(rt), L, R, v);
    }
    if (mid < R) {
        update(rs(rt), L, R, v);
    }
    pushup(rt);
}
ll query(int rt, int L, int R) {
    auto &l = tr[rt].l;
    auto &r = tr[rt].r;
    if (l >= L && r <= R) {
        return tr[rt].sum;
    }
    pushdown(rt);
    int mid = (l + r) / 2;
    ll res  = 0;
    if (L <= mid) {
        res += query(ls(rt), L, R);
    }
    if (mid < R) {
        res += query(rs(rt), L, R);
    }
    return res;
}
int find(int l, int r) {
    int x = 1;
    while (l < r) {
        pushdown(x);
        int mid = (l + r) / 2;
        if (2 * tr[rs(x)].siz >= tr[1].siz) {
            l = mid + 1;
            x = rs(x);
        } else {
            r = mid;
            x = ls(x);
        }
    }
    return pos[l];
}
#undef ls
#undef rs
} // namespace SegmentTree
void range_add(int x, int v) {
    while (top[x] != 1) {
        SegmentTree::update(1, id[top[x]], id[x], v);
        x = fa[top[x]];
    }
    SegmentTree::update(1, 1, id[x], v);
}
ll range_query(int x) {
    ll res = 0;
    while (top[x] != 1) {
        res += SegmentTree::query(1, id[top[x]], id[x]);
        x = fa[top[x]];
    }
    res += SegmentTree::query(1, 1, id[x]);
    return res;
}
ll sume = 0, sumdis = 0;
ll solve(int rt) {
    return sumdis + dis[rt] * sume - 2ll * range_query(rt);
}
int n, q;
signed main() {
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        Tr.add(u, v, w);
        Tr.add(v, u, w);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    SegmentTree::build(1, 1, n);
    while (q--) {
        int x, e;
        cin >> x >> e;
        sume += e;
        sumdis += dis[x] * e;
        range_add(x, e);
        cout << solve(SegmentTree::find(1, n)) << endl;
    }
    return 0;
}
// Asusetic eru quionours
```

#线段树