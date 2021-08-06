#include <array>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
const int K = 10005;
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
        b >>= 1;
    }
    return res;
}
ll inv(int x) {
    return qpow(x, -1);
}
ll n, k;
ll dp[52][K];
ll ans = 1;
ll solve(int cnt, int k, ll num) {
    if (dp[cnt][k]) {
        return dp[cnt][k] % mod;
    }
    if (cnt == 0) {
        dp[cnt][k] = 1;
        return 1;
    }
    if (k == 0) {
        dp[cnt][k] = (solve(cnt - 1, k, num) * num) % mod;
        return dp[cnt][k];
    }
    ll res = 0;
    for (int i = 0; i <= cnt; i++) {
        res = (res + solve(i, k - 1, num)) % mod;
    }
    dp[cnt][k] = (res * inv(cnt + 1)) % mod;
    return dp[cnt][k] % mod;
}

int main() {
    cin >> n >> k;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int cnt = 0;
            while (n % i == 0) {
                cnt++;
                n /= i;
            }
            memset(dp, 0, sizeof(dp));
            ans = (ans * solve(cnt, k, i)) % mod;
        }
    }
    if (n > 1) {
        memset(dp, 0, sizeof(dp));
        ans = (ans * solve(1, k, n) % mod) % mod;
    }
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours