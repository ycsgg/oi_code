#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
constexpr int K = 5005;
constexpr ll mod = 1e9 + 7;
ll n, k;
ll S[K][K];
void pre() {
    S[0][0] = 1;
    for (int i = 1; i < K; i++) {
        for (int j = 1; j <= i; j++) {
            S[i][j] = (S[i - 1][j - 1] + 1ll * S[i - 1][j] * j % mod) % mod;
        }
    }
}
ll qpow(ll a, ll b) {
    b %= mod - 1;
    if (b < 0)
        b += mod - 1;
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
    cin >> n >> k;
    pre();
    auto p2 = qpow(2, n);
    auto inv2 = qpow(2, -1);
    ll ans = 0;
    ll frac = 1;
    for (int i = 0; i <= k; i++) {
        ans = (ans + 1ll * frac * S[k][i] % mod * p2 % mod) % mod;
        frac = frac * (n - i) % mod;
        p2 = p2 * inv2 % mod;
    }
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours