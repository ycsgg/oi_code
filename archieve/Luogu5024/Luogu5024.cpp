#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#define int long long
using namespace std;
int read() {
    int x = 0, k = 1;
    char c = getchar();
    for (; c < 48 || c > 57; c = getchar())
        k ^= (c == '-');
    for (; c >= 48 && c <= 57; c = getchar())
        x = x * 10 + (c ^ 48);
    return k ? x : -x;
}

const int N = 1e5 + 5, INF = 2e9;
int n, m, sum, num, tim, head[N], a[N], ldp[N][2], dp[N][2];
int siz[N], fa[N], dep[N], son[N], top[N], id[N], bel[N], ed[N];
struct Edge {
    int nxt, v;
} edge[N * 2];

void addedge(int u, int v) {
    edge[++num].nxt = head[u], edge[num].v = v, head[u] = num;
    edge[++num].nxt = head[v], edge[num].v = u, head[v] = num;
}

void dfs1(int x) {
    dep[x] = dep[fa[x]] + 1, siz[x] = 1;
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v != fa[x]) {
            fa[v] = x;
            dfs1(v);
            siz[x] += siz[v];
            if (siz[v] > siz[son[x]]) {
                son[x] = v;
            }
        }
    }
}

void dfs2(int x, int topf) {
    top[x] = topf;
    id[x] = ed[topf] = ++tim;
    bel[tim]         = x;
    if (son[x])
        dfs2(son[x], topf);
    for (int i = head[x], v; i; i = edge[i].nxt)
        if ((v = edge[i].v) != fa[x] && v != son[x])
            dfs2(v, v);
}

void dfs3(int x) {
    for (int i = head[x], v; i; i = edge[i].nxt)
        if ((v = edge[i].v) != fa[x] && v != son[x]) {
            dfs3(v);
            ldp[x][0] += std::max(dp[v][0], dp[v][1]);
            ldp[x][1] += dp[v][0];
        }
    dp[x][0] += ldp[x][0], dp[x][1] += ldp[x][1]; //
    if (!son[x])
        return;
    dfs3(son[x]);
    dp[x][0] += std::max(dp[son[x]][0], dp[son[x]][1]);
    dp[x][1] += dp[son[x]][0];
}

struct Matrix {
    int m[2][2];
    Matrix() {
        m[0][0] = m[0][1] = m[1][0] = m[1][1] = -INF;
    }
    Matrix operator*(const Matrix &tmp) const {
        Matrix ans;
        ans.m[0][0] = ans.m[0][1] = ans.m[1][0] = ans.m[1][1] = -INF;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 2; ++k)
                    ans.m[i][j] = std::max(ans.m[i][j], m[i][k] + tmp.m[k][j]);
        return ans;
    }
} val[N];

Matrix New(int x, int y, int z, int w) {
    Matrix A;
    A.m[0][0] = x, A.m[0][1] = y, A.m[1][0] = z, A.m[1][1] = w;
    return A;
}

struct Segment_Tree {
#define ls p << 1
#define rs p << 1 | 1
    Matrix data[N << 2];
    int L[N << 2], R[N << 2];
    void build(int p, int l, int r) {
        L[p] = l, R[p] = r;
        if (l == r)
            return (void)(data[p] = val[bel[l]] =
                              New(ldp[bel[l]][0], ldp[bel[l]][0],
                                  ldp[bel[l]][1], -INF));
        int Mid = (l + r) >> 1;
        build(ls, l, Mid), build(rs, Mid + 1, r);
        data[p] = data[ls] * data[rs];
    }
    void update(int p, int pos) {
        if (L[p] == R[p])
            return (void)(data[p] = val[bel[pos]]);
        int Mid = (L[p] + R[p]) >> 1;
        update(pos <= Mid ? ls : rs, pos);
        data[p] = data[ls] * data[rs];
    }
    Matrix query(int p, int l, int r) {
        if (L[p] >= l && R[p] <= r)
            return data[p];
        int Mid = (L[p] + R[p]) >> 1;
        if (l > Mid)
            return query(rs, l, r);
        if (r <= Mid)
            return query(ls, l, r);
        return query(ls, l, r) * query(rs, l, r);
    }
} T;

void change(int u, int w) {
    val[u].m[1][0] += w, a[u] += w;
    while (u) {
        int now     = top[u];
        Matrix last = T.query(1, id[now], ed[now]);
        T.update(1, id[u]);
        Matrix nxt = T.query(1, id[now], ed[now]);
        u          = fa[now];
        val[u].m[0][0] += std::max(nxt.m[0][0], nxt.m[1][0]) -
                          std::max(last.m[0][0], last.m[1][0]);
        val[u].m[0][1] = val[u].m[0][0];
        val[u].m[1][0] += nxt.m[0][0] - last.m[0][0];
    }
}

int query() {
    Matrix ans = T.query(1, id[1], ed[1]);
    return std::max(ans.m[0][0], ans.m[1][0]);
}

signed main() {
    char tmp[3];
    cin >> n >> m >> tmp;
    for (int i = 1; i <= n; ++i) {
        ldp[i][1] = a[i] = read();
        sum += a[i];
    }
    for (int i = 1; i < n; ++i) {
        int u = read(), v = read();
        addedge(u, v);
    }
    dfs1(1), dfs2(1, 1), dfs3(1);
    T.build(1, 1, n);
    while (m--) {
        int a, b, x, y;
        cin >> a >> x >> b >> y;
        if ((fa[a] == b || fa[b] == a) && !x && !y) {
            cout << -1 << endl;
            continue;
        }
        change(a, x ? -INF : INF);
        change(b, y ? -INF : INF);

        printf("%lld\n", sum - query() + (x ? 0 : INF) + (y ? 0 : INF));
        change(a, x ? INF : -INF);
        change(b, y ? INF : -INF);
    }
    return 0;
}