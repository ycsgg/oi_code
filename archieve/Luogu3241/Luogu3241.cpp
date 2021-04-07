#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 150005;
struct Edge {
    int v;
    int w, nxt;
} edge[N * 2];
int head[N], ecnt;
void add(int u, int v, int w) {
    edge[++ecnt].v = v;
    edge[ecnt].w   = w;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
struct QAQ {
    int f;
    ll dis;
    int typ;
};
int tot;
vector<QAQ> fa[N];
struct Data {
    int val;
    ll ss, sv;
    friend bool operator<(const Data &A, const Data &B) {
        return A.val < B.val;
    }
};
vector<Data> ans[N][3];
int val[N];
int n, m;
ll A;
int siz[N];
bool vis[N], cut[N];
int dep[N];
int rt;
void getsiz(int x) {
    siz[x] = 1;
    vis[x] = 1;
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (!vis[v] && !cut[v]) {
            getsiz(v);
            siz[x] += siz[v];
        }
    }
    vis[x] = 0;
}
int minv;
void getrt(int x) {
    vis[x]   = 1;
    int maxv = tot - siz[x];
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (!vis[v] && !cut[v]) {
            getrt(v);
            maxv = max(maxv, siz[v]);
        }
    }
    vis[x] = 0;
    if (maxv < minv) {
        minv = maxv;
        rt   = x;
    }
}

void getdep(int x, int g, int cnt) {
    vis[x] = 1;
    fa[x].push_back((QAQ){g, dep[x], cnt});
    ans[g][cnt].push_back((Data){val[x], 1, dep[x]});
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (!vis[v] && !cut[v]) {
            dep[v] = dep[x] + edge[i].w;
            getdep(v, g, cnt);
        }
    }
    vis[x] = 0;
}
void build(int x) {
    getsiz(x);
    if (siz[x] == 1) {
        cut[x] = 1;
        fa[x].push_back((QAQ){x, 0, -1});
        return;
    }
    tot  = siz[x];
    rt   = 0;
    minv = 0x3f3f3f3f;
    getrt(x);
    cut[rt] = 1;
    fa[rt].push_back((QAQ){rt, 0, -1});
    int cnt = 0;
    for (int i = head[rt]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (cut[v])
            continue;
        dep[v] = edge[i].w;
        getdep(v, rt, cnt);
        ans[rt][cnt].push_back((Data){0x3f3f3f3f, 0, 0});
        sort(ans[rt][cnt].begin(), ans[rt][cnt].end());
        for (int j = ans[rt][cnt].size() - 2; j >= 0; j--) {
            ans[rt][cnt][j].ss += ans[rt][cnt][j + 1].ss;
            ans[rt][cnt][j].sv += ans[rt][cnt][j + 1].sv;
        }
        cnt++;
    }
    for (int i = head[rt]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (!cut[v])
            build(v);
    }
}
ll query(int l, int r, int u) {
    ll res = 0;
    vector<Data>::iterator L;
    vector<Data>::iterator R;
    for (int i = fa[u].size() - 1; i >= 0; i--) {
        int f = fa[u][i].f;
        for (int typ = 0; typ <= 2; typ++) {
            if (typ == fa[u][i].typ || ans[f][typ].empty()) {
                continue;
            }
            L = lower_bound(ans[f][typ].begin(), ans[f][typ].end(),
                            (Data){l, 0, 0});
            R = upper_bound(ans[f][typ].begin(), ans[f][typ].end(),
                            (Data){r, 0, 0});
            res += fa[u][i].dis * (L->ss - R->ss) + L->sv - R->sv;
        }
        if (l <= val[f] && val[f] <= r) {
            res += fa[u][i].dis;
        }
    }
    return res;
}
signed main() {
    cin >> n >> m >> A;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
    }
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    build(1);
    ll res = 0;
    for (int i = 1; i <= m; i++) {
        int u;
        ll l;
        ll r;
        scanf("%d%lld%lld", &u, &l, &r);
        (l += res) %= A;
        (r += res) %= A;
        if (l > r)
            swap(l, r);
        res = query(l, r, u);
        cout << res << endl;
    }
}