#include <iostream>
#include <vector>
using namespace std;
#define int ll
using ll = long long;
const int N = 110;
const ll mod = 1e9 + 7;
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
} G;
ll dp[N][N][2];
ll siz[N], tmp[N][2];
int qpow(int x, int b) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = res * x % mod;
        }
        x = x * x % mod;
        b >>= 1;
    }
    return res;
}
void dfs(int x, int fa) {
    dp[x][0][0] = dp[x][0][1] = 1;
    siz[x] = 0;
    for (int v : G.edge[x]) {
        if (v == fa)
            continue;
        dfs(v, x);
        for (int j = 0; j <= siz[x] + siz[v] + 1; ++j) {
            tmp[j][0] = tmp[j][1] = 0;
        }
        for (int j = 0; j <= siz[x]; j++) {
            for (int k = 0; k <= siz[v]; k++) {
                tmp[j + k][0] =
                    (tmp[j + k][0] + dp[x][j][0] * dp[v][k][1] % mod) % mod;
                tmp[j + k][1] =
                    (tmp[j + k][1] + dp[x][j][1] * dp[v][k][1] % mod) % mod;
                tmp[j + k + 1][0] =
                    (tmp[j + k + 1][0] + dp[x][j][0] * dp[v][k][0] % mod) % mod;
                tmp[j + k + 1][1] =
                    (tmp[j + k + 1][1] + dp[x][j][0] * dp[v][k][1] % mod) % mod;
                tmp[j + k + 1][1] =
                    (tmp[j + k + 1][1] + dp[x][j][1] * dp[v][k][0] % mod) % mod;
            }
        }
        for (int j = 0; j <= siz[x] + siz[v] + 1; j++) {
            dp[x][j][0] = tmp[j][0];
            dp[x][j][1] = tmp[j][1];
        }
        siz[x] += siz[v] + 1;
    }
}
int fac[101], ifac[101];
int C(int x, int y) {
    return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
int n;
signed main() {
    fac[0] = 1;
    for (int i = 1; i <= 100; ++i) {
        fac[i] = fac[i - 1] * i % mod;
    }
    ifac[100] = qpow(fac[100], mod - 2);
    for (int i = 99; i >= 0; --i) {
        ifac[i] = ifac[i + 1] * (i + 1) % mod;
    }
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        G.add(u, v);
        G.add(v, u);
    }
    dfs(1, 0);
    for (int k = 0; k < n - 1; k++) {
        dp[1][k][1] = dp[1][k][1] * qpow(n, (n - k) - 2) % mod;
    }
    dp[1][n - 1][1] = 1;
    for (int k = 0; k < n; ++k) {
        ll ans = 0;
        for (int l = k; l < n; ++l)
            (ans += (((l - k) & 1) ? mod - C(l, k) * dp[1][l][1] % mod
                                   : C(l, k) * dp[1][l][1] % mod)) %= mod;
        printf("%lld ", ans);
    }
}