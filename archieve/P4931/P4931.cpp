#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const int N  = 5e6 + 500;
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
struct Query {
    ll n, k;
} q[300005];
ll T, n;
ll fac[N], invfac[N], f[N], inv[N];
int main() {
    cin >> T;
    fac[0] = fac[1] = invfac[0] = invfac[1] = inv[1] = 1;
    for (int i = 1; i <= T; i++) {
        cin >> q[i].n >> q[i].k;
        n = max(q[i].n, n);
    }
    f[0] = 1;
    f[1] = 0;
    for (int i = 2; i <= n; i++) {
        f[i] = 4ll * i * (1ll * i - 1ll) % mod * f[i - 1] % mod +
               8ll * i * (1ll * i - 1ll) % mod * (1ll * i - 1ll) % mod *
                   f[i - 2] % mod;
    }
    for (int i = 1; i <= n; i++) {
        fac[i] = 1ll * fac[i - 1] * i % mod;
    }
    invfac[n] = qpow(fac[n], mod - 2);
    for (int i = n - 1; i >= 2; i--) {
        invfac[i] = 1ll * invfac[i + 1] * 1ll * (i + 1) % mod;
    }
    for (int i = 1; i <= n; i++) {
        fac[i] = 1ll * fac[i] * fac[i] % mod;
    }
    for (int i = 1; i <= T; i++) {
        cout << 1ll * fac[q[i].n] % mod * invfac[q[i].k] % mod *
                    invfac[q[i].n - q[i].k] % mod * invfac[q[i].n - q[i].k] %
                    mod * qpow(2, q[i].k) % mod * f[q[i].n - q[i].k] % mod
             << endl;
    }
    return 0;
}