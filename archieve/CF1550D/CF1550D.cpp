#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
const int N = 2e5 + 10;
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
ll fac[N], ifac[N];
ll C(int n, int m) {
    if (n < m || n < 0 || m < 0) {
        return 0;
    }
    return fac[n] * ifac[n - m] % mod * ifac[m] % mod;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    fac[0] = ifac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    ifac[N - 1] = qpow(fac[N - 1], mod - 2);
    for (int i = N - 2; i >= 1; i--) {
        ifac[i] = ifac[i + 1] * (i + 1) % mod;
    }

    int _;
    cin >> _;

    while (_--) {
        ll n, l, r;
        cin >> n >> l >> r;
        auto C1 = C(n, n / 2) % mod;
        if (n & 1) {
            C1 = (C1 + C(n, n / 2 + 1)) % mod;
        }
        ll len = max(0ll, min(1 - l, r - n));
        auto ans = len * C1 % mod;
        int k = min(1 - l, r - n) + 1;
        while (true) {
            auto lb = max(1ll, l + k);
            auto rb = min(n, r - k);
            auto C2 = C(rb - lb + 1, n / 2 - (lb - 1)) % mod;
            if (n & 1) {
                C2 = (C2 + C(rb - lb + 1, n / 2 + 1 - (lb - 1))) % mod;
            }
            if (!C2) {
                break;
            }
            ans = (ans + C2) % mod;
            k++;
        }
        cout << ans << '\n';
    }

    return 0;
}
// Asusetic eru quionours.