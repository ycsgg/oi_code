#include <algorithm>
#include <iostream>
using namespace std;
using ll     = long long;
const int N  = 2005;
const ll mod = 1e9 + 9;
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
ll dp[N][N];
ll fac[N], ifac[N], g[N];
int a[N], b[N], lb[N];
int n, k;
ll C(int n, int m) {
    if (n < m)
        return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
int main() {
    cin >> n >> k;
    if ((n + k) & 1) {
        cout << 0 << endl;
        return 0;
    }
    k      = (n + k) / 2;
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = 1ll * i * fac[i - 1] % mod;
    }
    ifac[n] = qpow(fac[n], mod - 2);
    for (int i = n - 1; i >= 1; i--) {
        ifac[i] = 1ll * (i + 1) * ifac[i + 1] % mod;
    }
    ifac[1] = 1;
    ifac[0] = 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    sort(a + 1, a + 1 + n);
    sort(b + 1, b + 1 + n);
    int cur = 0;
    for (int i = 1; i <= n; i++) {
        while (cur < n && b[cur + 1] < a[i])
            cur++;
        lb[i] = cur;
    }
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i][0] = dp[i - 1][0];
        for (int j = 1; j <= i; j++) {
            dp[i][j] = (dp[i - 1][j] +
                        dp[i - 1][j - 1] * max(0, lb[i] - j + 1) % mod) %
                       mod;
        }
    }
    for (int i = 0; i <= n; i++) {
        g[i] = dp[n][i] * fac[n - i] % mod;
    }
    ll ans = 0;
    for (int i = k; i <= n; i++) {
        if ((i - k) & 1) {
            ans -= 1ll * C(i, k) * g[i] % mod;
            ans = (ans + mod) % mod;
        } else {
            ans += 1ll * C(i, k) * g[i] % mod;
            ans %= mod;
        }
    }
    cout << (ans + mod) % mod;
}
// Asusetic eru quionours
