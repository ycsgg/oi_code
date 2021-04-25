#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 998244353, g = 3;
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
ll inv(ll x) {
    return qpow(x, mod - 2);
}
const int N = 2e6 + 5;
ll n, p, k;
ll w[N];
ll ans;
int main() {
    cin >> n >> p >> k;
    w[0] = 1;
    w[1] = qpow(g, (mod - 1) / k);
    for (int i = 2; i < N; i++) {
        w[i] = w[i - 1] * w[1] % mod;
    }
    ans =
        (n * p % mod * qpow(p + 1, n - 1) % mod + qpow(p + 1, n)) % mod; // d==0
    for (int d = 1; d < k; d++) {
        ll now = w[d] * qpow(w[d] * p % mod + 1 % mod, n) % mod;
        now    = (now - qpow(p + 1, n) + mod) % mod;
        ans    = (ans + now * inv((w[d] - 1 + mod) % mod)) % mod;
    }
    ans = ans * inv(k) % mod;
    ans = (ans - qpow(p + 1, n) + mod) % mod;
    cout << ans;
    return 0;
}
// Asusetic eru quionours
