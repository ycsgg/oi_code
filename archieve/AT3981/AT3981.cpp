#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
const int LIM = 21;
const ll mod  = 1e9 + 7;
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
int n, m;
ll a[LIM];
ll pow2[LIM];
ll g[LIM][(1 << LIM) + 5];
ll fac[(1 << LIM) + 5], ifac[(1 << LIM) + 5];
ll C(int n, int m) {
    if (n < m)
        return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + 1 + m);
    reverse(a + 1, a + 1 + m);
    pow2[0] = 1;
    for (int i = 1; i < LIM; i++) {
        pow2[i] = pow2[i - 1] << 1ll;
    }
    fac[0] = 1;
    for (int i = 1; i <= pow2[LIM - 1]; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    ifac[pow2[LIM - 1]] = qpow(fac[pow2[LIM - 1]], mod - 2);
    for (int i = pow2[LIM - 1] - 1; i >= 0; i--) {
        ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
    }
    g[0][0] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < pow2[n]; j++) {
            g[i][j] = (g[i][j] + g[i - 1][j]) % mod;
            for (int k = 0; k < n; k++) {
                if (j & pow2[k])
                    continue;
                g[i][(j | pow2[k])] =
                    (g[i][(j | pow2[k])] +
                     g[i - 1][j] * C(pow2[n] - j - a[i], pow2[k] - 1) % mod *
                         fac[pow2[k]] % mod) %
                    mod;
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < pow2[n]; i++) {
        int res = __builtin_popcount(i);
        if (res & 1) {
            ans = (ans - g[m][i] * fac[pow2[n] - 1 - i] + mod) % mod;
        } else {
            ans = (ans + g[m][i] * fac[pow2[n] - 1 - i]) % mod;
        }
    }
    cout << ans * pow2[n] % mod;
    return 0;
}