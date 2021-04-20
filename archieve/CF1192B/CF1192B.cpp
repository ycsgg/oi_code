// #include <dbg>
#include <iostream>
#include <set>
using namespace std;
typedef long long ll;
const int N = 1e6;
struct Edge {
    int v;
    ll w;
    int nxt;
} edge[N * 2];
int head[N], ecnt;
void add(int u, int v, ll w) {
    edge[++ecnt].v = v;
    edge[ecnt].w   = w;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
int n, m;
ll w;
int id[N * 2];
const ll INF = 20000000000000ll + 15ll;
struct Matrix {
    ll a[3][3];
    ll *operator[](const int x) {
        return a[x];
    }
    const ll *operator[](const int x) const {
        return a[x];
    }
    Matrix() {
    }
    Matrix(ll _a, ll b, ll c, ll d, ll e, ll f, ll g, ll h, ll i) {
        a[0][0] = _a;
        a[0][1] = b;
        a[0][2] = c;
        a[1][0] = d;
        a[1][1] = e;
        a[1][2] = f;
        a[2][0] = g;
        a[2][1] = h;
        a[2][2] = i;
    }
    Matrix operator*(const Matrix &b) const {
        Matrix c;
        c.a[0][0] = max(max(a[0][0] + b.a[0][0], a[0][1] + b.a[1][0]),
                             a[0][2] + b.a[2][0]);
        c.a[0][1] = max(max(a[0][0] + b.a[0][1], a[0][1] + b.a[1][1]),
                             a[0][2] + b.a[2][1]);
        c.a[0][2] = max(max(a[0][0] + b.a[0][2], a[0][1] + b.a[1][2]),
                             a[0][2] + b.a[2][2]);
        c.a[1][0] = max(max(a[1][0] + b.a[0][0], a[1][1] + b.a[1][0]),
                             a[1][2] + b.a[2][0]);
        c.a[1][1] = max(max(a[1][0] + b.a[0][1], a[1][1] + b.a[1][1]),
                             a[1][2] + b.a[2][1]);
        c.a[1][2] = max(max(a[1][0] + b.a[0][2], a[1][1] + b.a[1][2]),
                             a[1][2] + b.a[2][2]);
        c.a[2][0] = max(max(a[2][0] + b.a[0][0], a[2][1] + b.a[1][0]),
                             a[2][2] + b.a[2][0]);
        c.a[2][1] = max(max(a[2][0] + b.a[0][1], a[2][1] + b.a[1][1]),
                             a[2][2] + b.a[2][1]);
        c.a[2][2] = max(max(a[2][0] + b.a[0][2], a[2][1] + b.a[1][2]),
                             a[2][2] + b.a[2][2]);
        // EXPAND!!
        return c;
    }
};
struct DelHeap {
    typedef multiset<ll, greater<ll>>::iterator iter;
    multiset<ll, greater<ll>> s;
    ll top() {
        return s.empty() ? 0 : *s.begin();
    }
    void push(const ll &x) {
        s.insert(x);
    }
    void del(ll x) {
        iter it = s.find(x);
        if (it == s.end())
            return;
        s.erase(it);
    }
    ll top2() {
        if (s.empty())
            return 0;
        iter it = s.begin();
        ll mx   = *it;
        if (s.size() == 1)
            return mx;
        return mx + *(++it);
    }
};
namespace LCT {
int fa[N], ch[N][2];
ll val[N];
ll g[N][2];
Matrix ret[N];
DelHeap g0[N], g1[N];
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
void pushup(int x) {
    ll tmp0 = max(g0[x].top(), g1[x].top2());
    ll tmp1 = g1[x].top();
    ret[x]  = Matrix(0, tmp1, tmp0, -INF, val[x], val[x] + tmp1, -INF, -INF, 0);
    if (ls(x)) {
        ret[x] = ret[ls(x)] * ret[x];
    }
    if (rs(x)) {
        ret[x] = ret[x] * ret[rs(x)];
    }
}
bool identity(int x) {
    return ch[fa[x]][1] == x;
}
bool isroot(int x) {
    return (ch[fa[x]][0] != x) && (ch[fa[x]][1] != x);
}
void rotate(const int &x) {
    int y = fa[x], z = fa[y];
    int k = identity(x);
    if (!isroot(y)) {
        ch[z][identity(y)] = x;
    }
    ch[y][k]     = ch[x][k ^ 1];
    ch[x][k ^ 1] = y;
    fa[ch[y][k]] = y;
    fa[y]        = x;
    fa[x]        = z;
    pushup(y);
}
void splay(const int &x) {
    while (!isroot(x)) {
        int y = fa[x];
        if (!isroot(y)) {
            rotate(identity(x) ^ identity(y) ? x : y);
        }
        rotate(x);
    }
    pushup(x);
}
void access(int x) {
    int y = 0;
    while (x) {
        splay(x);
        if (rs(x)) {
            g0[x].push(max(ret[rs(x)][0][1], ret[rs(x)][0][2]));
            g1[x].push(ret[rs(x)][1][2]);
        }
        if (y) {
            g0[x].del(max(ret[y][0][1], ret[y][0][2]));
            g1[x].del(ret[y][1][2]);
        }
        rs(x) = y;
        pushup(x);
        y = x;
        x = fa[x];
    }
}
void update(ll x, ll y) {
    access(x);
    val[x] = y;
    pushup(x);
    splay(x);
}
ll query() {
    splay(1);
    return ret[1][0][2];
}
void dfs(int x) {
    ll mmax = 0, submax = 0;
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == fa[x])
            continue;
        fa[v]            = x;
        val[v]           = edge[i].w;
        id[(i + 1) >> 1] = v;
        dfs(v);
        g1[x].push(g[v][1]);
        g0[x].push(g[v][0]);
        g[x][0] = max(g[x][0], g[v][0]);
        if (g[v][1] > mmax) {
            submax = mmax;
            mmax   = g[v][1];
        } else if (g[v][1] > submax) {
            submax = g[v][1];
        }
    }
    g[x][1] = mmax + val[x];
    g[x][0] = max(g[x][0], mmax + submax);
    pushup(x);
}
#undef ls
#undef rs
} // namespace LCT

int main() {
    cin >> n >> m >> w;
    for (int i = 1; i < n; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, w);
    }
    LCT::dfs(1);
    ll lastans = 0;
    while (m--) {
        ll x;
        ll p;
        cin >> x >> p;
        x = (x + lastans) % (n - 1) + 1ll;
        p = (p + lastans) % w;
        LCT::update(id[x], p);
        lastans = LCT::query();
        cout << lastans << endl;
    }
    return 0;
}
// Asusetic eru quionours
