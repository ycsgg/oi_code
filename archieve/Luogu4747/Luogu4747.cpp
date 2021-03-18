#include <iostream>
using namespace std;
const int N = 200005;
int n, m;
int a[N];
int pow2[25];
struct RMQ {
    int lg[N], mmax[N][17], mmin[N][17];
    void build() {
        pow2[0] = 1;
        for (int i = 1; i < 20; i++) {
            pow2[i] = pow2[i - 1] * 2;
        }
        for (int i = 2; i <= n; i++) {
            lg[i] = lg[i >> 1] + 1;
        }
        for (int i = 1; i <= n; i++) {
            mmax[i][0] = mmin[i][0] = a[i];
        }
        for (int i = 1; i < 17; i++) {
            for (int j = 1; j + pow2[i] - 1 <= n; j++) {
                mmin[j][i] = min(mmin[j][i - 1], mmin[j + pow2[i - 1]][i - 1]);
                mmax[j][i] = max(mmax[j][i - 1], mmax[j + pow2[i - 1]][i - 1]);
            }
        }
    }
    int query_min(int l, int r) {
        int k = lg[r - l + 1];
        return min(mmin[l][k], mmin[r - pow2[k] + 1][k]);
    }
    int query_max(int l, int r) {
        int k = lg[r - l + 1];
        return max(mmax[l][k], mmax[r - pow2[k] + 1][k]);
    }
} Table;
struct SegmentTree {
#define ls x * 2
#define rs x * 2 + 1
    int mmin[N * 4], tag[N * 4];
    void pushup(int x) {
        mmin[x] = min(mmin[ls], mmin[rs]);
    }
    void pushdown(int x) {
        if (tag[x]) {
            mmin[ls] += tag[x];
            tag[ls] += tag[x];
            mmin[rs] += tag[x];
            tag[rs] += tag[x];
            tag[x] = 0;
        }
    }
    void update(int x, int l, int r, int L, int R, int v) {
        if (l > R || r < L) {
            return;
        }
        if (l >= L && r <= R) {
            mmin[x] += v;
            tag[x] += v;
            return;
        }
        pushdown(x);
        int mid = (l + r) / 2;
        if (R <= mid) {
            update(ls, l, mid, L, R, v);
        } else if (L > mid) {
            update(rs, mid + 1, r, L, R, v);
        } else {
            update(ls, l, mid, L, R, v);
            update(rs, mid + 1, r, L, R, v);
        }
        pushup(x);
    }
    int query(int x, int l, int r) {
        if (l == r) {
            return l;
        }
        pushdown(x);
        int mid = (l + r) / 2;
        if (mmin[ls] == 0) {
            return query(ls, l, mid);
        } else {
            return query(rs, mid + 1, r);
        }
    }
#undef ls
#undef rs
} Tr;
int top1, top2, st1[N], st2[N];
int top, st[N];
int id[N], lp[N], rp[N], cnt, dep[N];
int fa[N][21];
bool check(int l, int r) {
    return (Table.query_max(l, r) - Table.query_min(l, r)) == r - l;
}
struct Edge {
    int v;
    int nxt;
} edge[N * 2];
int head[N * 2], ecnt = 1;
void add(int u, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
void dfs(int x) {
    for (int i = 1; (1 << i) <= dep[x]; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v    = edge[i].v;
        dep[v]   = dep[x] + 1;
        fa[v][0] = x;
        dfs(v);
    }
}
int jump(int u, int d) {
    for (int i = 0; i < 18 && d; ++i)
        if (pow2[i] & d) {
            d ^= pow2[i];
            u = fa[u][i];
        }
    return u;
}
int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);
    x = jump(x, dep[x] - dep[y]);
    if (x == y)
        return x;
    for (int i = 17; i >= 0; i--) {
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}
int typ[N], M[N];
int rt;
void build() {
    for (int i = 1; i <= n; i++) {
        while (top1 && a[i] <= a[st1[top1]]) {
            Tr.update(1, 1, n, st1[top1 - 1] + 1, st1[top1], a[st1[top1]]);
            top1--;
        }
        while (top2 && a[i] >= a[st2[top2]]) {
            Tr.update(1, 1, n, st2[top2 - 1] + 1, st2[top2], -a[st2[top2]]);
            top2--;
        }
        Tr.update(1, 1, n, st1[top1] + 1, i, -a[i]);
        st1[++top1] = i;
        Tr.update(1, 1, n, st2[top2] + 1, i, a[i]);
        st2[++top2] = i;
        id[i]       = ++cnt;
        lp[cnt] = rp[cnt] = i;
        int ls = Tr.query(1, 1, n), now = cnt;
        while (top && lp[st[top]] >= ls) {
            if (typ[st[top]] && check(M[st[top]], i)) {
                rp[st[top]] = i;
                add(st[top], now);
                now = st[top];
                top--;
            } else if (check(lp[st[top]], i)) {
                typ[++cnt] = 1;
                lp[cnt]    = lp[st[top]];
                rp[cnt]    = i;
                M[cnt]     = lp[now];
                add(cnt, st[top]);
                add(cnt, now);
                top--;
                now = cnt;
            } else {
                add(++cnt, now);
                do {
                    add(cnt, st[top]);
                    top--;
                } while (top && !check(lp[st[top]], i));
                lp[cnt] = lp[st[top]];
                rp[cnt] = i;
                add(cnt, st[top]);
                top--;
                now = cnt;
            }
        }
        st[++top] = now;
        Tr.update(1, 1, n, 1, i, -1);
    }
    rt = st[1];
}
pair<int, int> query(int l, int r) {
    int x = id[l], y = id[r];
    int z = lca(x, y);
    if (typ[z] & 1) {
        l = lp[jump(x, dep[x] - dep[z] - 1)];
        r = rp[jump(y, dep[y] - dep[z] - 1)];
    } else
        l = lp[z], r = rp[z];
    return make_pair(l, r);
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    Table.build();
    build();
    dfs(rt);
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        pair<int, int> p = query(x, y);
        cout << p.first << " " << p.second << endl;
    }
    return 0;
}