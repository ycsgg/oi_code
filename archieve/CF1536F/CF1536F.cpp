#include <array>
#include <iostream>
using namespace std;
using ll    = long long;
const int mod = 1e9 + 7;
const int N = 2e6 + 5;
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
array<ll, N> fac, ifac;
ll C(int n, int m) {
    if (n < m)
        return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
ll f(int n, int m) {
    return (C(n, m) + C(n - 1, m - 1)) % mod;
}
int n;
int main() {
    cin >> n;
    fac[0] = 1, ifac[0] = 1;
    for (int i = 1; i <= n + 1; ++i) {
        fac[i] = fac[i - 1] * i % mod;
    }
    ifac[n + 1] = qpow(fac[n + 1], mod - 2);
    for (int i = n; i >= 1; i--) {
        ifac[i] = ifac[i + 1] * (i + 1) % mod;
    }
    ll ans = 0;
    for (int i = 2; i <= n; i += 2) {
        ans = (ans + fac[i] * f(i, n - i) % mod) % mod;
    }
    printf("%lld\n", ans * 2 % mod);
    return 0;
}
// Asusetic eru quionours