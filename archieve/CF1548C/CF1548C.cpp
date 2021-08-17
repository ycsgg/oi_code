#include <algorithm>
#include <iostream>
using namespace std;
using ll = long long;
const int mod = 1e9 + 7;
const int N = 3e6 + 10;
ll n, q, inv[N], fac[N], ifac[N], ans[N], f[N];
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
    cin >> n >> q;
    fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
    for (int i = 2; i <= 3 * n + 3; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    ifac[3 * n + 3] = qpow(fac[3 * n + 3], mod - 2);
    for (int i = 3 * n + 2; i >= 2; i--) {
        ifac[i] = ifac[i + 1] * (i + 1) % mod;
    }
    for (int i = 0; i < 3 * n + 3; i++) {
        ans[i] = C(3 * n + 3, i + 1);
    }
    ans[0] = (ans[0] - 3 + mod) % mod, ans[1] = (ans[1] - 3 + mod) % mod,
    ans[2] = (ans[2] - 1 + mod) % mod;
    for (int i = 3 * n + 2; i >= 2; i--) {
        f[i - 2] = ans[i];
        ans[i] -= f[i - 2], ans[i - 1] -= f[i - 2] * 3,
            ans[i - 2] -= f[i - 2] * 3;
        ans[i - 1] = (ans[i - 1] % mod + mod) % mod,
                ans[i - 2] = (ans[i - 2] % mod + mod) % mod;
    }
    while (q--) {
        int x;
        cin >> x;
        cout << f[x] << endl;
    }
    return 0;
}
// Asusetic eru quionours.