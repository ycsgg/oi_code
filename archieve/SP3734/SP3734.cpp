#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 505;
const int M = 1e6 + 10;
const ll mod = 1e9 + 7;
int n, k;
int h[N];
int st[N], top, ch[N][2];
ll fac[M], ifac[M];
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
ll C(int n, int m) {
    if (n < m || n < 0 || m < 0) {
        return 0;
    }
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
ll dp[N][N];
int siz[N];
void dfs(int x, int pre) {
    dp[x][0] = 1;
    siz[x] = 1;
    if (ch[x][0]) {
        auto v = ch[x][0];
        dfs(v, h[x]);
        siz[x] += siz[v];
        for (int i = min(siz[x], k); i >= 0; i--) {
            for (int j = 1; j <= min(siz[v], i); j++) {
                dp[x][i] = (dp[x][i] + dp[v][j] * dp[x][i - j] % mod) % mod;
            }
        }
    }
    if (ch[x][1]) {
        auto v = ch[x][1];
        dfs(v, h[x]);
        siz[x] += siz[v];
        for (int i = min(siz[x], k); i >= 0; i--) {
            for (int j = 1; j <= min(siz[v], i); j++) {
                dp[x][i] = (dp[x][i] + dp[v][j] * dp[x][i - j] % mod) % mod;
            }
        }
    }
    for (int i = min(siz[x], k); i >= 0; i--) {
        for (int j = 1; j <= min(h[x] - pre, i); j++) {
            dp[x][i] =
                (dp[x][i] + fac[j] * dp[x][i - j] % mod * C(h[x] - pre, j) %
                                mod * C(siz[x] - i + j, j) % mod) %
                mod;
        }
    }
}
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < M; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    ifac[M - 1] = qpow(fac[M - 1], mod - 2);
    for (int i = M - 2; i >= 1; i--) {
        ifac[i] = ifac[i + 1] * (i + 1) % mod;
    }
    for (int i = 1; i <= n; i++) {
        int tmp = top;
        while (top && h[st[top]] > h[i]) {
            top--;
        }
        if (top) {
            ch[st[top]][1] = i;
        }
        if (top != tmp) {
            ch[i][0] = st[top + 1];
        }
        st[++top] = i;
    }
    dfs(st[1], 0);
    cout << dp[st[1]][k] << '\n';
    return 0;
}
// Asusetic eru quionours.