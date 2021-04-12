#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 2e5 + 5;
int n, m;
int a[MAXN];
int to[MAXN], nxt[MAXN], head[MAXN], ecnt;
void add(int u, int v) {
    to[++ecnt] = v;
    nxt[ecnt]  = head[u];
    head[u]    = ecnt;
}
int dep[MAXN];
int stt[20][MAXN], lg2[MAXN], id1[MAXN], tot;
void dfs1(int u, int last, int depth) {
    dep[u]        = depth;
    stt[0][++tot] = u;
    id1[u]        = tot;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == last) {
            continue;
        }
        dfs1(v, u, depth + 1);
        stt[0][++tot] = u;
    }
}
int Lower(int x, int y) {
    return dep[x] < dep[y] ? x : y;
}
void RMQinit() {
    for (int i = 2; i <= tot; i++)
        lg2[i] = lg2[i >> 1] + 1;
    for (int i = 1; (1 << i) <= tot; i++) {
        int w = (1 << i);
        for (int j = 1; j + w - 1 <= tot; j++) {
            stt[i][j] = Lower(stt[i - 1][j], stt[i - 1][j + w / 2]);
        }
    }
}
int getLCA(int x, int y) {
    x = id1[x];
    y = id1[y];
    if (x > y)
        swap(x, y);
    int i = lg2[y - x + 1], w = (1 << i);
    return Lower(stt[i][x], stt[i][y - w + 1]);
}
int dis(int x, int y) {
    return dep[x] + dep[y] - 2 * dep[getLCA(x, y)];
}

int siz[MAXN], mmax[MAXN];
int dfa[MAXN];
int vis[MAXN];
int dsiz[MAXN];
int dfs2(int u, int last, int tots) {
    siz[u]  = 1;
    mmax[u] = 0;
    int _rt = 0;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (vis[v] || v == last)
            continue;
        int vrt = dfs2(v, u, tots);
        if (!_rt || mmax[vrt] < mmax[_rt]) {
            _rt = vrt;
        }
        siz[u] += siz[v];
        mmax[u] = max(mmax[u], siz[v]);
    }
    mmax[u] = max(mmax[u], tots - siz[u]);
    if (!_rt || mmax[u] < mmax[_rt])
        _rt = u;
    return _rt;
}
void solve(int _rt, int tots) {
    vis[_rt]  = 1;
    dsiz[_rt] = tots;
    for (int i = head[_rt]; i; i = nxt[i]) {
        int v = to[i];
        if (vis[v]) {
            continue;
        }
        int vsize = (siz[v] < siz[_rt]) ? siz[v] : (tots - siz[_rt]);
        int vrt   = dfs2(v, _rt, vsize);
        dfa[vrt]  = _rt;
        solve(vrt, vsize);
    }
}
struct Node {
    int sum;
    Node *ch[2];
};
Node mempool[10000000];
int ncnt;
struct SegTree {
    Node *rt;
    SegTree() {
        rt = NULL;
    }
    Node *newnode() {
        return &mempool[ncnt++];
    }
    void modify(Node *&now, int pos, int k, int l, int r) {
        if (!now) {
            now = newnode();
        }
        now->sum += k;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            modify(now->ch[0], pos, k, l, mid);
        else
            modify(now->ch[1], pos, k, mid + 1, r);
    }
    int query(Node *now, int l, int r, int nl, int nr) {
        if (!now)
            return 0;
        if (l == nl && r == nr)
            return now->sum;
        int mid = (nl + nr) >> 1;
        if (r <= mid)
            return query(now->ch[0], l, r, nl, mid);
        else if (l > mid)
            return query(now->ch[1], l, r, mid + 1, nr);
        return query(now->ch[0], l, mid, nl, mid) +
               query(now->ch[1], mid + 1, r, mid + 1, nr);
    }
};

SegTree tr1[MAXN], tr2[MAXN];

void modify(int idx, int val) {
    int now = idx;
    while (now) {
        int fa = dfa[now];
        tr1[now].modify(tr1[now].rt, dis(now, idx), val, 0, dsiz[now]);
        if (fa)
            tr2[now].modify(tr2[now].rt, dis(fa, idx), val, 0, dsiz[fa]);
        now = fa;
    }
}

int query(int idx, int k) {
    int res = 0;
    int now = idx, last = 0;
    while (now) {
        int d = dis(idx, now);
        if (d > k) {
            last = now;
            now  = dfa[now];
            continue;
        }
        res += tr1[now].query(tr1[now].rt, 0, k - d, 0, dsiz[now]);
        if (last)
            res -= tr2[last].query(tr2[last].rt, 0, k - d, 0, dsiz[now]);
        last = now;
        now  = dfa[now];
    }
    return res;
}

void pre() {
    dfs1(1, 0, 0);
    RMQinit();
    int _rt = dfs2(1, 0, n);
    solve(_rt, n);
    for (int i = 1; i <= n; i++) {
        modify(i, a[i]);
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n - 1; i++) {
        int x, y;
        cin >> x >> y;
        add(x, y);
        add(y, x);
    }
    pre();
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        int op, x, y;
        cin >> op >> x >> y;
        x ^= ans;
        y ^= ans;
        if (op == 0) {
            ans = query(x, y);
            cout << ans << endl;
        } else {
            modify(x, y - a[x]);
            a[x] = y;
        }
    }
    return 0;
}