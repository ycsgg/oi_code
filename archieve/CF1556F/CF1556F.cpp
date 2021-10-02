#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
const int N = 15;
int n;
ll h[N][1 << N];
ll dp[N][1 << N];
ll g(ll S, ll T) {
    ll res = 1;
    for (int i = 0; i < n; i++) {
        if (S & (1 << i)) {
            res = (1ll * res * h[i][T] % mod) % mod;
        }
    }
    return res;
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
    cin >> n;
    vector<int> a(n);
    for (auto &v : a) {
        cin >> v;
    }
    for (int x = 0; x < n; x++) {
        for (int S = 1; S < (1 << n); S++) {
            h[x][S] = 1;
            if (S & (1 << x)) {
                continue;
            }
            for (int y = 0; y < n; y++) {
                if (S & (1 << y)) {
                    h[x][S] = (h[x][S] * a[y] % mod *
                               qpow((a[x] + a[y]) % mod, mod - 2) % mod) %
                              mod;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int S = 1; S < (1 << n); S++) {
            if (!(S & (1 << i))) {
                continue;
            }
            dp[i][S] = 1;
            for (int T = (S - 1) & S; T; T = (T - 1) & S) {
                if (!(T & (1 << i))) {
                    continue;
                }
                // printf("%d(%d) -> %d : %lld\n",T,i,S,g(T,S-T));
                dp[i][S] =
                    (dp[i][S] - 1ll * dp[i][T] * g(T, S - T) % mod + mod) % mod;
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans = (ans + dp[i][(1 << n) - 1]) % mod;
    }
    cout << ans;
    return 0;
}
// Asusetic eru quionours.
