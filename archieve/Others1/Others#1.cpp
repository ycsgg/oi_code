#include "../old/Polynomial.cpp"
#include <iostream>
using namespace std;
using Poly::Polynomial;
using Poly::qpow;
const int N = 5e5 + 5;
typedef long long ll;
ll fac[N], ifac[N], inv[N];
const ll mod = 998244353;
int n, m, k;
Polynomial<ll> f, g, d;
int main() {
    inv[1] = fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
    for (int i = 2; i <= N; i++) {
        inv[i]  = -mod / i * inv[mod % i] % mod;
        fac[i]  = fac[i - 1] * i % mod;
        ifac[i] = ifac[i - 1] * inv[i] % mod;
    }
    cin >> n >> m >> k;
    f.resize(m + 2);
    g.resize(m + 2);
    for (int i = 0; i <= m + 1; i++) {
        f[i] = (i & 1 ? -1 : 1) * ifac[i] % mod * ifac[m + 1 - i] % mod;
        g[i] = qpow(i, m);
    }
    d = f * g;
    for (int i = 0; i < m; i++) {
        f[i] = 1ll * d[i + 1] * (m + 1) % mod;
    }
    for (int i = m - 1; i >= 0; i--)
        f[i] = (f[i] + f[i + 1]) % mod;
    for (int i = 0; i < m; i++)
        f[i] = qpow(f[i], n) % mod;
    for (int i = 0; i < m; i++)
        f[i] = (f[i] - f[i + 1]) % mod;
    ll ans = 0;
    for (int i = 0; i < m; i++)
        ans = (ans + qpow(i, k) * f[i]) % mod;
    ans = (ans % mod + mod) % mod;
    printf("%lld\n", ans);
    return 0;
}