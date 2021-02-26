#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 19260817;
inline ll qpow(ll a, ll b) {
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
const int N = 1000005;
ll phi[N], fac[N];
ll cnt, prime[N];
inline void init() {
    phi[1] = 1;
    for (ll i = 2; i < N; ++i) {
        if (!phi[i]) {
            phi[i]       = i - 1;
            prime[++cnt] = i;
        }
        for (ll j = 1; j <= cnt && prime[j] * i < N; ++j) {
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
    fac[0] = 1;
    for (ll i = 1; i < N; ++i) {
        phi[i] = (phi[i] + phi[i - 1]) % (mod - 1);
        fac[i] = fac[i - 1] * i % mod;
    }
}

int T;
ll n, ans;
int main() {
    init();
    cin >> T;
    while (T--) {
        cin >> n;
        ans = 1;
        for (ll l = 1, r; l <= n; l = r + 1) {
            r   = n / (n / l);
            ans = ans *
                  qpow(fac[r] * qpow(fac[l - 1], mod - 2) % mod, phi[n / l]) %
                  mod;
        }
        ans = qpow(fac[n], 2 * n + 2) * qpow(ans, mod - 5) % mod;
        cout << ans << endl;
    }
    return 0;
}