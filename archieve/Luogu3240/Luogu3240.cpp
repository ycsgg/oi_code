#include <iostream>
#include <map>
using namespace std;
const int N = 5005;
typedef long long ll;
const ll mod = 1e9 + 7;
int n, m;
enum Type {
    VOID = -1,
    Equal,
    Less,
};
struct Oper {
    int u, v;
    Type typ;
} q[N];
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
int fa[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y) {
    x     = find(x);
    y     = find(y);
    fa[x] = y;
}
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b /= 2;
    }
    return res;
}
ll fac[N], ifac[N];
void init() {
    fac[0] = 1;
    for (int i = 1; i <= n + 1; ++i)
        fac[i] = 1ll * fac[i - 1] * i % mod;
    ifac[n + 1] = qpow(fac[n + 1], mod - 2);
    for (int i = n; i >= 0; --i) {
        ifac[i] = 1ll * ifac[i + 1] * (1ll * i + 1ll) % mod;
    }
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
}
int in[N];
int dp[N][N];
bool G[N][N];
bool vis[N], flag = 1;
void dfs(int x) {
    if (vis[x]) {
        cout << 0 << endl;
        exit(0);
    }
    vis[x]  = 1;
    int cnt = 0;
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        dfs(v);
        cnt++;
    }
    if (cnt) {
        for (int i = 1; i <= n; i++) {
            dp[x][i] = 1;
        }
        for (int i = head[x]; i; i = edge[i].nxt) {
            int v = edge[i].v;
            for (int j = 1; j <= n; j++) {
                dp[x][j] = 1ll * dp[x][j] * dp[v][j - 1] % mod;
            }
        }
        for (int i = 1; i <= n; i++) {
            dp[x][i] = (1ll * dp[x][i] + 1ll * dp[x][i - 1] % mod) % mod;
        }
        return;
    } else {
        for (int i = 1; i <= n; i++) {
            dp[x][i] = i;
        }
    }
}
ll C(int n, int m) {
    return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
int main() {
    cin >> n >> m;
    char rub[3];
    init();
    for (int i = 1; i <= m; i++) {
        cin >> q[i].u >> rub >> q[i].v;
        if (rub[0] == '=') {
            q[i].typ = Equal;
            merge(q[i].u, q[i].v);
        } else {
            q[i].typ = Less;
        }
    }
    for (int i = 1; i <= m; i++) {
        if (q[i].typ == Equal) {
            continue;
        }
        int x = find(q[i].u), y = find(q[i].v);
        if (!G[x][y]) {
            add(x, y);
            G[x][y] = 1;
        }
        in[y]++;
    }
    bool QAQ = 1;
    for (int i = 1; i <= n; i++) {
        if (find(i) == i && in[i] == 0) {
            add(0, i);
            QAQ = 0;
        }
    }
    n++;
    dfs(0);
    for (int i = 1; i <= n - 1; i++) {
        if (!vis[find(i)]) {
            cout << 0 << endl;
            return 0;
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j & 1) {
                ans = (ans + mod - (1ll * C(i, j) % mod * dp[0][i - j]) % mod) %
                      mod;
            } else {
                ans = (ans + 1ll * C(i, j) % mod * dp[0][i - j] % mod) % mod;
            }
        }
    }
    cout << ans << endl;
}
// Asusetic eru quionours