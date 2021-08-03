#include <array>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 5;
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
};
int n, m;
int dep[N], siz[N], fa[N], son[N];
void dfs1(int x, int _fa, const Graph &G) {
    dep[x] = dep[_fa] + 1;
    siz[x] = 1;
    for (auto v : G.edge[x]) {
        if (v == _fa) {
            continue;
        }
        fa[v] = x;
        dfs1(v, x, G);
        siz[x] += siz[v];
        if (siz[v] > siz[son[x]]) {
            son[x] = v;
        }
    }
};
int id[N], tim, top[N], w[N], val[N];
void dfs2(int x, int topf, const Graph &G) {
    id[x] = ++tim;
    // printf("%d : %d\n", x, id[x]);
    top[x] = topf;
    val[tim] = w[x];
    if (!son[x])
        return;
    dfs2(son[x], topf, G);
    for (auto v : G.edge[x]) {
        // cout << v << " <---------- " << x << endl;
        if (v == fa[x] || v == son[x]) {
            continue;
        }
        dfs2(v, v, G);
    }
}
struct SegmentTree {
#define ls(x) (x * 2)
#define rs(x) (x * 2 + 1)
    struct Node {
        int tag, res, lval, rval;
        int l, r;
    };
    array<Node, N * 4> tr;
    void pushup(int x) {
        tr[x].res =
            tr[ls(x)].res + tr[rs(x)].res + (tr[ls(x)].rval == tr[rs(x)].lval);
        tr[x].lval = tr[ls(x)].lval;
        tr[x].rval = tr[rs(x)].rval;
    }
    void pushdown(int x) {
        if (!tr[x].tag)
            return;
        auto &l = tr[x].l;
        auto &r = tr[x].r;
        int mid = (l + r) / 2;
        tr[ls(x)].res = mid - l;
        tr[rs(x)].res = r - mid - 1;
        tr[ls(x)].tag = tr[x].tag;
        tr[rs(x)].tag = tr[x].tag;
        tr[ls(x)].lval = tr[ls(x)].rval = tr[x].tag;
        tr[rs(x)].lval = tr[rs(x)].rval = tr[x].tag;
        tr[x].tag = 0;
    }
    void build(int x, int l, int r) {
        tr[x].l = l;
        tr[x].r = r;
        tr[x].tag = 0;
        if (l == r) {
            tr[x].res = 0;
            tr[x].lval = tr[x].rval = val[l];
            // printf("%d~%d : %d\n", l, r, val[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(ls(x), l, mid);
        build(rs(x), mid + 1, r);
        pushup(x);
    }
    int query(int x, int L, int R) {
        auto &l = tr[x].l;
        auto &r = tr[x].r;
        if (L <= l && r <= R) {
            return tr[x].res;
        }
        pushdown(x);
        int mid = (l + r) / 2;
        int res = 0;
        if (L <= mid) {
            res += query(ls(x), L, R);
        }
        if (mid < R) {
            res += query(rs(x), L, R);
        }
        if (L <= mid && mid < R && tr[ls(x)].rval == tr[rs(x)].lval) {
            res++;
        }
        return res;
    }
    void update(int x, int L, int R, int v) {
        auto &l = tr[x].l;
        auto &r = tr[x].r;
        // printf("%d %d %d %d %d\n", x, l, r, L, R);
        if (L <= l && r <= R) {
            tr[x].lval = tr[x].rval = v;
            tr[x].res = r - l;
            tr[x].tag = v;
            return;
        }
        pushdown(x);
        int mid = (l + r) / 2;
        if (L <= mid) {
            update(ls(x), L, R, v);
        }
        if (mid < R) {
            update(rs(x), L, R, v);
        }
        pushup(x);
    }
    int querypos(int x, int pos) {
        auto &l = tr[x].l;
        auto &r = tr[x].r;
        if (l == r) {
            return tr[x].lval;
        }
        pushdown(x);
        int mid = (l + r) / 2;
        if (pos <= mid) {
            return querypos(ls(x), pos);
        } else {
            return querypos(rs(x), pos);
        }
    }
#undef ls
#undef rs
};
int tot;
void update(int x, int y, SegmentTree &T) {
    ++tot;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            swap(x, y);
        }
        T.update(1, id[top[x]], id[x], tot);
        // printf("M : %d(%d) -> %d(%d) : %d\n", x, T.querypos(1, id[x]),
        // top[x],
        //        T.querypos(1, id[top[x]]), tot);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) {
        swap(x, y);
    }
    T.update(1, id[x], id[y], tot);
    // printf("M : %d(%d) -> %d(%d) : %d\n", x, T.querypos(1, id[x]), y,
    //        T.querypos(1, id[y]), tot);
}
int query(int x, int y, SegmentTree &T) {
    int res = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            swap(x, y);
        }
        res += T.query(1, id[top[x]], id[x]);
        // printf("Q : %d(%d) -> %d(%d) : %d\n", x, T.querypos(1, id[x]),
        // top[x],
        //        T.querypos(1, id[top[x]]), res);
        if (T.querypos(1, id[fa[top[x]]]) == T.querypos(1, id[top[x]]))
            res++;
        // printf("Q : %d(%d) -> %d(%d) : %d\n", top[x], T.querypos(1,
        // id[top[x]]),
        //        fa[top[x]], T.querypos(1, id[fa[top[x]]]), res);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) {
        swap(x, y);
    }
    res += T.query(1, id[x], id[y]);
    // printf("Q : %d(%d) -> %d(%d) : %d\n", x, T.querypos(1, id[x]), y,
    //        T.querypos(1, id[y]), res);
    return res;
}
void clear() {
    memset(son, 0, sizeof(son));
    memset(dep, 0, sizeof(dep));
    memset(id, 0, sizeof(id));
    tim = 0;
    tot = 0;
};
int main() {
    // freopen("edge.in", "r", stdin);
    // freopen("edge.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        clear();
        cin >> n >> m;
        SegmentTree ST;
        Graph Tr;
        for (int i = 1; i <= n; i++) {
            w[i] = ++tot;
        }
        for (int i = 1; i < n; i++) {
            int a, b;
            cin >> a >> b;
            // cout << a << " --------> " << b << endl;
            Tr.add(a, b);
            Tr.add(b, a);
        }
        dfs1(1, 0, Tr);
        dfs2(1, 1, Tr);
        ST.build(1, 1, n);
        while (m--) {
            int opt, x, y;
            cin >> opt >> x >> y;
            if (opt == 1) {
                update(x, y, ST);
            } else {
                cout << query(x, y, ST) << '\n';
            }
        }
    }
    cout.flush();
    // fclose(stdin);
    // fclose(stdout);
    return 0;
}
// Asusetic eru quionours