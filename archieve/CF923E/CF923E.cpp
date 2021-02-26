
#include "Polynomial.cpp"
#include <iostream>
using namespace std;
using namespace Poly;
Polynomial<long long> f, g;
const ll Mod   = 998244353;
const int maxn = 1e6 + 7;
typedef long long ll;
ll n, m;
ll fac[maxn], invfac[maxn];
ll a[maxn];
int main() {
    cin >> n >> m;
    n++;
    f.resize(n);
    g.resize(n);
    m %= (Mod - 1);
    fac[0] = 1;
    for (int i = 1; i < n; i++)
        fac[i] = 1ll * fac[i - 1] * i % Mod;
    invfac[n - 1] = invx(fac[n - 1]);
    for (int i = n - 2; i + 1; i--)
        invfac[i] = 1ll * invfac[i + 1] * (i + 1) % Mod;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        f[n - i - 1] = 1ll * fac[i] * a[i] % Mod;
    }
    for (int i = 0; i < n; i++) {
        g[i] = invfac[i];
    }
    f = f * g; // clac g_i^1
    f.resize(n);
    for (int i = 0; i < n; i++) {
        g[i] = 1ll * invfac[i] * f[n - i - 1] % Mod;
    }
    for (int i = 0; i < n; i++) {
        g[i] = 1ll * g[i] * invx(qpow(i + 1, m)) % Mod; // calc g_i^m
    }
    for (int i = 0; i < n; i++) {
        f[n - i - 1] = 1ll * fac[i] * g[i] % Mod;
    }
    for (int i = 0; i < n; i++) {
        g[i] = (i & 1) ? Mod - invfac[i] : invfac[i];
    }
    f = f * g;
    for (int i = 0; i < n; i++) {
        cout << 1ll * invfac[i] * f[n - i - 1] % Mod << " ";
    }
}


