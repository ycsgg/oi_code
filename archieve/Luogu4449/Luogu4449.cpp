#include <iostream>
using namespace std;
using ll      = long long;
const int N   = 5e6 + 10;
const int mod = 1e9 + 7;
int prime[N];
ll g0[N], g[N];
bool vis[N];
ll T, k, pcnt;
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
void Sieve() {
    g[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            g0[pcnt]      = qpow(i, k);
            g[i]          = (g0[pcnt] - 1 + mod) % mod;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (i * prime[j] >= N) {
                break;
            }
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                g[i * prime[j]] = 1ll * g[i] * g0[j] % mod;
                break;
            }
            g[i * prime[j]] = 1ll * g[i] * g[prime[j]] % mod;
        }
    }
    for (int i = 1; i < N; i++) {
        g[i] = (g[i] + g[i - 1]) % mod;
    }
}
int main() {
    cin >> T >> k;
    Sieve();
    while (T--) {
        int n, m, t;
        ll ans = 0;
        cin >> n >> m;
        t = min(n, m);
        for (ll l = 1, r; l <= t; l = r + 1) {
            r   = min(n / (n / l), m / (m / l));
            ans = (ans + 1ll * (g[r] - g[l - 1] + mod) * (n / l) % mod *
                             (m / l) % mod) %
                  mod;
        }
        cout << ans << endl;
    }
    return 0;
}
// Asusetic eru quionours