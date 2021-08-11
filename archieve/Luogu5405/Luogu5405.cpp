#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 998244353;
const int N = 1005;
struct Graph {
    vector<pair<int, ll>> edge[N];
    void add(int u, int v, int typ) {
        edge[u].emplace_back(make_pair(v, typ));
    }
} Tr;
ll qpow(ll a, ll b) {
    b %= mod - 1;
    if (b < 0) {
        b += mod - 1;
    }
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
int n;
ll p[N][4];
vector<vector<ll>> dp;
int siz[N];
void dfs(int x, int fa) {
    dp[x][0] = 1;
    for (auto &[v, typ] : Tr.edge[x]) {
        if (v == fa)
            continue;
        dfs(v, x);
        vector<ll> g((siz[x] + siz[v]) * 3 + 1, 0);
        for (int i = 0; i <= siz[x] * 3; i++) {
            for (int j = 0; j <= siz[v] * 3; j++) {
                g[i + j] =
                    (g[i + j] + dp[x][i] * dp[v][j] % mod * (mod + typ) % mod) %
                    mod;
                if (typ == -1) {
                    g[i] = (g[i] + dp[x][i] * dp[v][j] % mod) % mod;
                }
            }
        }
        dp[x] = g;
        siz[x] += siz[v];
    }
    vector<ll> g(siz[x] * 3 + 4, 0);
    for (int i = 0; i <= siz[x] * 3; i++) {
        for (int j = 1; j <= 3; j++) {
            g[i + j] = (g[i + j] + dp[x][i] * j % mod * qpow(i + j, -1) % mod *
                                       p[x][j] % mod) %
                       mod;
        }
    }
    dp[x] = g;
    siz[x] += 1;
}
signed main() {
    cin >> n;
    dp.assign(n * 3 + 1, vector<ll>(n * 3 + 1));
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        auto tmp = qpow(a + b + c, -1);
        p[i][1] = a * tmp % mod;
        p[i][2] = b * tmp % mod;
        p[i][3] = c * tmp % mod;
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        Tr.add(u, v, 1);
        Tr.add(v, u, -1);
    }
    dfs(1, 0);
    ll ans = 0;
    for (int i = 1; i <= 3 * n; i++) {
        ans = (ans + dp[1][i]) % mod;
    }
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours