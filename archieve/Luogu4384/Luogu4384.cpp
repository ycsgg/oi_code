#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 2e5 + 6;
char s[N];
int n, q;
struct Edge {
    int v;
    int nxt;
} edge[N * 4];
int head[N * 2], ecnt;
void add(int u, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
namespace SegmentTree {
const int maxn = 2e5 + 6;
struct Node {
    int mmin, mmax;
    long long s1, s2;
    int ls, rs;
} tr[maxn * 40];
int tot;
Node merge(const Node &a, const Node &b) {
    Node c;
    c.mmin = min(a.mmin, b.mmin);
    c.mmax = max(a.mmax, b.mmax);
    c.s1   = a.s1 + b.s1 + b.mmin * 1LL * (b.mmin - a.mmax);
    c.s2   = a.s2 + b.s2 + b.mmin - a.mmax;
    return c;
}
void pushup(int x) {
    if (tr[x].ls && tr[x].rs) {
        tr[x].mmin = min(tr[tr[x].ls].mmin, tr[tr[x].rs].mmin);
        tr[x].mmax = max(tr[tr[x].ls].mmax, tr[tr[x].rs].mmax);
        tr[x].s1 =
            tr[tr[x].ls].s1 + tr[tr[x].rs].s1 +
            tr[tr[x].rs].mmin * 1LL * (tr[tr[x].rs].mmin - tr[tr[x].ls].mmax);
        tr[x].s2 = tr[tr[x].ls].s2 + tr[tr[x].rs].s2 + tr[tr[x].rs].mmin -
                   tr[tr[x].ls].mmax;
    } else if (tr[x].ls) {
        int t_ls = tr[x].ls;
        int t_rs = tr[x].rs;
        tr[x]    = tr[tr[x].ls];
        tr[x].ls = t_ls;
        tr[x].rs = t_rs;
    } else {
        int t_ls = tr[x].ls;
        int t_rs = tr[x].rs;
        tr[x]    = tr[tr[x].rs];
        tr[x].ls = t_ls;
        tr[x].rs = t_rs;
    }
}
int querymax(int rt, int l, int r, int L, int R) {
    if (!rt)
        return 0;
    if (L <= l && r <= R)
        return tr[rt].mmax;
    int mid = l + r >> 1, ans = 0;
    if (L <= mid)
        ans = querymax(tr[rt].ls, l, mid, L, R);
    if (R > mid)
        ans = max(ans, querymax(tr[rt].rs, mid + 1, r, L, R));
    return ans;
}
int querymin(int rt, int l, int r, int L, int R) {
    if (!rt)
        return 0x3f3f3f3f;
    if (L <= l && r <= R)
        return tr[rt].mmin;
    int mid = l + r >> 1, ans = 0x3f3f3f3f;
    if (L <= mid)
        ans = querymin(tr[rt].ls, l, mid, L, R);
    if (R > mid)
        ans = min(ans, querymin(tr[rt].rs, mid + 1, r, L, R));
    return ans;
}
Node c_res;
void cquery(int rt, int l, int r, int L, int R) {
    if (!rt)
        return;
    if (L <= l && r <= R) {
        if (c_res.mmin == 0)
            c_res = tr[rt];
        else
            c_res = merge(c_res, tr[rt]);
        return;
    }
    int mid = l + r >> 1;
    if (L <= mid)
        cquery(tr[rt].ls, l, mid, L, R);
    if (R > mid)
        cquery(tr[rt].rs, mid + 1, r, L, R);
}
void update(int &rt, int l, int r, int p) {
    if (!rt)
        rt = ++tot;
    if (l == r) {
        tr[rt].mmin = tr[rt].mmax = p;
        tr[rt].s1 = tr[rt].s2 = 0;
        tr[rt].ls = tr[rt].rs = 0;
        return;
    }
    int mid = l + r >> 1;
    if (p <= mid)
        update(tr[rt].ls, l, mid, p);
    else
        update(tr[rt].rs, mid + 1, r, p);
    pushup(rt);
}
int Merge(int x, int y) {
    if (!x || !y)
        return x + y;
    int rt    = ++tot;
    tr[rt].ls = Merge(tr[x].ls, tr[y].ls);
    tr[rt].rs = Merge(tr[x].rs, tr[y].rs);
    pushup(rt);
    return rt;
}
} // namespace SegmentTree

int rt[N], dep[N], fa[N * 2][19];
int pos[N];
namespace SAM {
int nxt[N * 2][10], link[N * 2], len[N * 2];
int cnt, last;
void insert(int c, int id) {
    int cur = ++cnt;
    int p   = last;
    last    = cur;
    pos[id] = cur;
    while (p && !nxt[p][c]) {
        nxt[p][c] = cur;
        p         = link[p];
    }
    if (!p) {
        link[cur] = 1;
    } else {
        int q = nxt[p][c];
        if (len[p] + 1 == len[q]) {
            link[cur] = q;
        } else {
            int cq  = ++cnt;
            len[cq] = len[p] + 1;
            memcpy(nxt[cq], nxt[q], sizeof(nxt[q]));
            link[cq] = link[q];
            link[q] = link[cur] = cq;
            while (p && nxt[p][c] == q) {
                nxt[p][c] = cq;
                p         = link[p];
            }
        }
    }
}
void dfs(int x);
void build() {
    for (int i = 1; i <= cnt; i++) {
        if (link[i]) {
            add(link[i], i);
        }
    }
    for (int i = 1; i <= n; i++) {
        SegmentTree::update(rt[pos[i]], 1, n, i);
    }
    dfs(1);
}
void dfs(int x) {
    fa[x][0] = link[x];
    for (int i = 1; i <= 18; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v  = edge[i].v;
        dep[v] = dep[x] + 1;
        dfs(v);
        if (x != 1) {
            rt[x] = SegmentTree::Merge(rt[x], rt[v]);
        }
    }
}
} // namespace SAM
ll C2(int n) {
    if (n < 2) {
        return 0;
    }
    return 1ll * n * (n - 1) / 2;
}
long long querym(int l, int r) {
    using SAM::len;
    using namespace SegmentTree;
    int plen = r - l + 1, x = pos[r];
    for (int i = 18; i >= 0; i--) {
        if (len[fa[x][i]] >= plen) {
            x = fa[x][i];
        }
    }
    int L = tr[rt[x]].mmin, R = tr[rt[x]].mmax;
    if (L < R - plen * 2 + 1 &&
        querymax(rt[x], 1, n, L, R - plen) - plen + 1 > L)
        return C2(n - 1);
    if (R - plen + 1 <= L) {
        Node now = tr[rt[x]];
        int lm   = R - plen + 1;
        long long ans =
            now.s1 - now.s2 * lm + C2(L - lm) + (L - lm) * 1LL * (n - plen);
        return C2(n - 1) - ans;
    } else {
        c_res  = (Node){0, 0, 0, 0, 0, 0};
        int lm = R - plen + 1, poslm = querymax(rt[x], 1, n, 1, lm);
        cquery(rt[x], 1, n, poslm, L + plen - 1);
        Node now      = c_res;
        int p1        = querymax(rt[x], 1, n, 1, L + plen - 1);
        int p2        = querymin(rt[x], 1, n, L + plen, n);
        long long ans = now.s1 - now.s2 * lm +
                        (p2 > lm ? (L - (p1 - plen + 1)) * 1LL * (p2 - lm) : 0);
        return C2(n - 1) - ans;
    }
}
int main() {
    cin >> n >> q;
    cin >> s + 1;
    SAM::last = SAM::cnt = 1;
    for (int i = 1; i <= n; i++) {
        SAM::insert(s[i] - '0', i);
    }
    SAM::build();
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << querym(l, r) << endl;
    }
    return 0;
}