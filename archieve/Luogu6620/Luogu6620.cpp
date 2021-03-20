#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define ROF(i, a, b) for (int i = a; i >= b; i--)
#define FOR(i, a, b) for (int i = a; i <= b; i++)
const int N = 1e3 + 1;
int n, x, m, s, mod, ans, a[N], f[N][N];
void check(int &x) {
    x -= mod;
    x += x >> 31 & mod;
}
int Pow(ll t, int x, ll s) {
    for (; x; x >>= 1, t = t * t % mod)
        if (x & 1)
            s = s * t % mod;
    return s;
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
int main() {
    cin >> n >> x >> mod >> m;
    f[0][0] = s = 1;
    for (int i = 0; i <= m; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= i; j++) {
            if (j) {
                f[i][j] = f[i - 1][j - 1];
            }
            f[i][j] =
                (f[i][j] + 1ll * (1 - i % mod + mod) * f[i - 1][j] % mod) % mod;
        }
    }
    for (int i = m; i >= 1; i--) {
        for (int j = 0; j <= i - 1; j++) {
            a[j] = (a[j] + mod - 1ll * f[i][j] * a[i] % mod) % mod;
        }
    }
    for (int i = 0; i <= m; i++) {
        ans = (ans + 1ll * s * qpow(x, i) % mod * qpow(x + 1, n - i) % mod *
                         a[i] % mod) %
              mod;
        s = 1ll * s * (n - i) % mod;
    }
    cout << ans;
    return 0;
}