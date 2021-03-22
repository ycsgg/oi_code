#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

const int mod = 1e9 + 7;
const int N   = 1e6 + 10;

ll l[N], r[N], fac[N];

ll qpow(ll a, ll b) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b /= 2;
    }
    return res;
}
int n, k, y = 0;
ll ans = 0;
int main() {
    cin >> n >> k;
    l[0] = r[k + 3] = fac[0] = 1;
    for (int i = 1; i <= k + 2; i++) {
        l[i] = 1ll * l[i - 1] * (n - i) % mod;
    }
    for (int i = k + 2; i >= 1; i--) {
        r[i] = 1ll * r[i + 1] * (n - i) % mod;
    }
    for (int i = 1; i <= k + 2; i++) {
        fac[i] = 1ll * fac[i - 1] * i % mod;
    }
    for (int i = 1; i <= k + 2; i++) {
        y    = (y + qpow(i, k)) % mod;
        ll a = l[i - 1] * 1ll * r[i + 1] % mod;
        ll b = fac[i - 1] * ((k - i) & 1 ? -1ll : 1ll) * fac[k + 2 - i] % mod;
        ans  = (ans + 1ll * y * a % mod * qpow(b, mod - 2) % mod) % mod;
    }
    printf("%d\n", (ans + mod) % mod);
    return 0;
}