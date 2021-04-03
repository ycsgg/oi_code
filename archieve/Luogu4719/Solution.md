### P4719 【模板】"动态 DP"&动态树分治

说白了就是维护一类树上的 dp 问题且支持修改点/边权

对于本题朴素的 dp 就是$f_{i,0}=\sum_v \max(f_{v,0},f_{v,1}) \quad f_{i,1}=w_i+\sum_v f_{v,0}$ 意义自明

而对于带修的操作我们考虑类似树链剖分的做法

设$g_{i,0/1}$表示不选/选$i$时只能选轻儿子的答案

那么$f_{i,0}=g_{i,0}+\max(f_{son_i,0},f_{son_i,1}) \quad f_{i,1}=g_{i,1}+f_{son_i,0}$

定义广义的矩阵乘法$C=A\times B$为$C_{i,j}=\max(A_{i,k}+B_{k,j})$ 其实也不必要是$\max$ 只要满足结合律能快速幂就行,那么
$$
\begin{gathered}
\begin{bmatrix} g_{i,0} & g_{i,0} \\ g_{i,1} & 0 \end{bmatrix}\times\begin{bmatrix}f_{son_i,0} \\f_{son_i,1} \end{bmatrix}=\begin{bmatrix}f_{i,0}\\f_{i,1}\end{bmatrix}
\quad
\end{gathered}
$$

修改仅需修改$g_{i,1}$和重链

用$dfs$预处理$f,g$，然后树剖，重链用线段树维护$g$矩阵和区间乘

```cpp
#include <cstring>
// #include <dbg>
#include <iostream>
using namespace std;
const int N   = 5e5 + 10;
struct Matrix {
    int a[2][2];
    Matrix() {
        memset(a, 0, sizeof(a));
    }
    int *operator[](int x) {
        return a[x];
    }
    Matrix operator*(Matrix b) {
        Matrix res;
        for (int i = 0; i < 2; i++) {
            for (int k = 0; k < 2; k++) {
                for (int j = 0; j < 2; j++) {
                    res[i][j] = max(res[i][j], a[i][k] + b[k][j]);
                }
            }
        }
        return res;
    }
} G[N];
struct Edge {
    int v;
    int nxt;
} edge[N * 2];
int head[N], ecnt;
void add(int u, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
int n, m;
int top[N], pos[N], id[N], cnt, endpos[N];
int a[N], dep[N], fa[N];
int f[N][2], siz[N], son[N];
namespace SegmentTree {
Matrix tr[N];
#define ls(x) x * 2
#define rs(x) x * 2 + 1
void pushup(int x) {
    tr[x] = tr[ls(x)] * tr[rs(x)];
}
void build(int rt, int l, int r) {
    if (l == r) {
        tr[rt] = G[id[l]];
        return;
    }
    int mid = (l + r) / 2;
    build(ls(rt), l, mid);
    build(rs(rt), mid + 1, r);
    pushup(rt);
}
Matrix query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return tr[rt];
    }
    int mid = (l + r) / 2;
    if (R <= mid) {
        return query(ls(rt), l, mid, L, R);
    }
    if (mid < L) {
        return query(rs(rt), mid + 1, r, L, R);
    }
    return query(ls(rt), l, mid, L, R) * query(rs(rt), mid + 1, r, L, R);
}
void update(int rt, int l, int r, int pos) {
    if (l == r) {
        tr[rt] = G[id[l]];
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        update(ls(rt), l, mid, pos);
    } else {
        update(rs(rt), mid + 1, r, pos);
    }
    pushup(rt);
}
void change(int x, int val) {
    G[x][1][0] += val - a[x];
    a[x]       = val;
    while (x) {
        Matrix last = query(1, 1, n, pos[top[x]], endpos[top[x]]);
        update(1, 1, n, pos[x]);
        Matrix now = query(1, 1, n, pos[top[x]], endpos[top[x]]);
        x          = fa[top[x]];
        G[x][0][0] += max(now[0][0], now[1][0]) - max(last[0][0], last[1][0]);
        G[x][0][1] = G[x][0][0];
        G[x][1][0] += now[0][0] - last[0][0];
    }
}
} // namespace SegmentTree

void dfs1(int x) {
    siz[x]  = 1;
    f[x][1] = a[x];
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == fa[x]) {
            continue;
        }
        fa[v]  = x;
        dep[v] = dep[x] + 1;
        dfs1(v);
        siz[x] += siz[v];
        if (siz[v] > siz[son[x]]) {
            son[x] = v;
        }
        f[x][1] += f[v][0];
        f[x][0] += max(f[v][0], f[v][1]);
    }
}
void dfs2(int x, int topf) {
    top[x]       = topf;
    pos[x]       = ++cnt;
    id[cnt]      = x;
    endpos[topf] = cnt;
    G[x][1][0]   = a[x];
    G[x][1][1]   = 0;
    if (!son[x]) {
        return;
    }
    dfs2(son[x], topf);
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == son[x] || v == fa[x]) {
            continue;
        }
        dfs2(v, v);
        G[x][0][0] += max(f[v][0], f[v][1]);
        G[x][1][0] += f[v][0];
    }
    G[x][0][1] = G[x][0][0];
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    dep[1] = 1;
    dfs1(1);
    dfs2(1, 1);
    SegmentTree::build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        int x, val;
        cin >> x >> val;
        SegmentTree::change(x, val);
        Matrix res = SegmentTree::query(1, 1, n, 1, endpos[1]);
        cout << max(res[0][0], res[1][0]) << endl;
    }
    return 0;
}
```

