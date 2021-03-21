#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 1000000007;
const int N  = 20000005;
ll f[N];
int prime[N], mu[N], pcnt;
bool vis[N];
void pre(ll lim) {
    f[1] = 1;
    for (ll i = 2; i <= lim; ++i) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            mu[i]         = -1;
            f[i]          = i * i % mod - 1;
        }
        for (ll j = 1; j <= pcnt; ++j) {
            if (prime[j] * i > lim) {
                break;
            }
            vis[i * prime[j]] = true;
            if (i % prime[j])
                f[i * prime[j]] = f[i] * f[prime[j]] % mod;
            else {
                f[i * prime[j]] = f[i] * prime[j] % mod * prime[j] % mod;
                break;
            }
        }
    }
    for (ll i = 2; i <= lim; ++i) {
        f[i] += f[i - 1];
        f[i] %= mod;
    }
}
ll calc(ll n, ll m) {
    if (n > m) {
        swap(n, m);
    }
    ll ans = 0;
    for (ll l = 1, r; l <= n; l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        ans += (f[r] - f[l - 1] + mod) * (n / l) % mod * (m / l) % mod;
        ans %= mod;
    }
    return ans % mod;
}
ll T, n, m, p;
int main() {
    cin >> T;
    pre(N-1);
    while (T-- > 0) {
        cin >> n >> m >> p;
        ll ans = ((n * calc(m, p) % mod + m * calc(n, p) % mod) % mod +
                  p * calc(n, m) % mod) %
                 mod;
        cout << ans << endl;
    }
    return 0;
}