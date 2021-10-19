#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 998244353;
const int M = 1e5 + 10;
const int N = 55;
int n, m;
bool vis[M];
int prime[M], pcnt, mu[M];
void Sieve(int lim) {
    mu[1] = 1;
    for (int i = 2; i <= lim; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (prime[j] * i > lim) {
                break;
            }
            vis[prime[j] * i] = 1;
            if (i % prime[j] == 0) {
                break;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
}
int l[N], r[N];
int _l[N], _r[N];
int f[M], g[M];
auto dp(int d) {
    for (int i = 1; i <= n; i++) {
        l[i] = (_l[i] / d + (_l[i] % d != 0));
        r[i] = _r[i] / d;
    }
    int sum = m / d;
    for (int i = 0; i <= sum; ++i) {
        f[i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            g[j] = 0;
        }
        for (int j = l[i]; j <= sum; j++) {
            g[j] = f[j - l[i]];
            if (j - r[i] - 1 >= 0) {
                g[j] = (g[j] - f[j - r[i] - 1] + mod) % mod;
            }
        }
        f[0] = 0;
        for (int j = 1; j <= sum; j++) {
            f[j] = (1ll * f[j - 1] + g[j]) % mod;
        }
    }
    return (1ll * f[sum] * mu[d] + mod) % mod;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    Sieve(m);

    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
        _l[i] = l[i];
        _r[i] = r[i];
    }

    ll ans = 0;
    for (int d = 1; d <= m; d++) {
        if (!mu[d]) {
            continue;
        }
        ans = (ans + dp(d) + mod) % mod;
    }
    cout << ans;

    return 0;
}
// Asusetic eru quionours.
