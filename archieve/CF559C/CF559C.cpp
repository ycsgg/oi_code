#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 2e5 + 10;
const ll mod = 1e9 + 7;
ll fac[N], ifac[N];
ll h, w, n;
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
ll C(int n, int m) {
    if (n < m) {
        return 0;
    }
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
int main() {
    cin >> h >> w >> n;
    vector<pair<int, int>> x(n);
    for (int i = 1; i <= n; i++) {
        cin >> x[i - 1].first >> x[i - 1].second;
    }
    x.push_back(make_pair(h, w));
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= h + w; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    ifac[h + w] = qpow(fac[h + w], mod - 2);
    for (int i = h + w - 1; i > 0; i--) {
        ifac[i] = ifac[i + 1] * (i + 1) % mod;
    }
    sort(x.begin(), x.end(),
         [&](const pair<int, int> &A, const pair<int, int> &B) -> bool {
             if (A.first == B.first) {
                 return A.second < B.second;
             }
             return A.first < B.first;
         });
    vector<ll> dp(n + 1);
    for (int i = 0; i <= n; i++) {
        dp[i] = C(x[i].first + x[i].second - 2, x[i].first - 1);
        for (int j = 0; j < i; j++) {
            dp[i] = (dp[i] -
                     dp[j] *
                         C(x[i].first - x[j].first + x[i].second - x[j].second,
                           x[i].first - x[j].first) %
                         mod +
                     mod) %
                    mod;
        }
    }
    cout << (dp[n] + mod) % mod;
    return 0;
}
// Asusetic eru quionours.