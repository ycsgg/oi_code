/*
さびしさや
一尺消えて
ゆくほたる
*/
#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
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
ll n, x, y, z;
ll S;
ll ans;
ll bitadd(ll x, ll i) {
    return ((x << i) | (1 << (i - 1))) & (S - 1);
}
ll mask;
bool check(ll state) {
    return ((state & mask) == mask);
}
int dp[42][(1 << 18)];
int main() {
    cin >> n >> x >> y >> z;
    ans  = qpow(10, n);
    mask = (1 << (x + y + z - 1));
    mask |= (1 << (y + z - 1));
    mask |= (1 << (z - 1));
    dp[0][0] = 1;
    S        = (1 << (x + y + z));
    for (int i = 1; i <= n; i++) {
        for (int s = 0; s < S; s++) {
            for (int k = 1; k <= 10; k++) {
                ll u = bitadd(s, k);
                if (!check(u)) {
                    dp[i][u] = (dp[i][u] + dp[i - 1][s]) % mod;
                }
            }
        }
    }
    for (int s = 0; s < S; s++) {
        ans = (ans - dp[n][s] + mod) % mod;
    }
    cout << ans << endl;
}
// Asusetic eru quionours