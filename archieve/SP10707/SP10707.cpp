#include <algorithm>
#include <iostream>
using namespace std;
const int N = 2e6 + 10;
const int block_size = 645;
int belong[N];
struct Oper {
    int id, l, r, ans, lca;
    friend bool operator<(const Oper &A, const Oper &B) {
        if (belong[A.l] == belong[B.l]) {
            return A.r < B.r;
        }
        return belong[A.l] < belong[B.l];
    }
} q[N];

struct Edge {
    int v;
    int nxt;
} edge[N];
int head[N], ecnt;
void add(int u, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
int n, m;
int c[N], b[N];
int fa[N], dep[N], top[N], siz[N], son[N];
int id1[N], id2[N], cnt, pos[N];
void dfs1(int x, int f) {
    fa[x]    = f;
    siz[x]   = 1;
    id1[x]   = ++cnt;
    pos[cnt] = x;
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == f) {
            continue;
        }
        dep[v] = dep[x] + 1;
        dfs1(v, x);
        siz[x] += siz[v];
        if (siz[v] > siz[son[x]]) {
            son[x] = v;
        }
    }
    id2[x]   = ++cnt;
    pos[cnt] = x;
}
void dfs2(int x, int topf) {
    top[x] = topf;
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
    }
}
int getlca(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            swap(x, y);
        }
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) {
        swap(x, y);
    }
    return x;
}
int cl[N], used[N], res[N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        b[i] = c[i];
    }
    sort(b + 1, b + 1 + n);
    for (int i = 1; i <= n; i++) {
        c[i] = lower_bound(b + 1, b + 1 + n, c[i]) - b;
    }
    for (int i = 1; i <= n * 2; i++) {
        belong[i] = i / block_size + 1;
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (id1[x] > id1[y]) {
            swap(x, y);
        }
        int lca = getlca(x, y);
        q[i].id = i;
        if (lca == x) {
            q[i].l = id1[x];
            q[i].r = id1[y];
        } else {
            q[i].l   = id2[x];
            q[i].r   = id1[y];
            q[i].lca = lca;
        }
    }
    sort(q + 1, q + 1 + m);
    int ans  = 0;
    auto add = [&](int x) -> void {
        ++cl[x];
        if (cl[x] == 1) {
            ans++;
        }
    };
    auto del = [&](int x) -> void {
        --cl[x];
        if (cl[x] == 0) {
            ans--;
        }
    };
    auto update = [&](int x) -> void {
        if (used[x]) {
            del(c[x]);
        } else {
            add(c[x]);
        }
        used[x] ^= 1;
    };
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        while (l < q[i].l) {
            update(pos[l]);
            l++;
        }
        while (l > q[i].l) {
            l--;
            update(pos[l]);
        }
        while (r < q[i].r) {
            r++;
            update(pos[r]);
        }
        while (r > q[i].r) {
            update(pos[r]);
            r--;
        }
        if (q[i].lca) {
            update(q[i].lca);
        }
        q[i].ans = ans;
        if (q[i].lca) {
            update(q[i].lca);
        }
    }
    for (int i = 1; i <= m; i++) {
        res[q[i].id] = q[i].ans;
    }
    for (int i = 1; i <= m; i++) {
        cout << res[i] << endl;
    }
    return 0;
}
