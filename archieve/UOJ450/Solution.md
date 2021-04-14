### 【集训队作业2018】复读机

~~单位根反演练习题~~

显然每个人的 EGF 是 $G=\sum\frac{[d|i]}{i!}x^i$

然后单位根反演 $[d|i]=\frac{1}{d}\sum\limits_{j=0}^{d-1}\omega^{ij}_d$

$G=\frac{1}{d}\sum\sum\limits_{j=0}^{d-1}\frac{\omega^{ij}_d}{i!}x^i=\frac{1}{d}\sum\limits_{j=0}^{d-1}\exp\omega^j_dx$

答案为 $[x^n]G^k(x)$

当 $d=2$ 时是 $(\frac{e^x+e^{-x}}{2})^k$

当 $d=3$ 时时 $(\frac{\exp \omega_3^0x+\exp \omega_3^1x+\exp \omega_3^2x}{3}^k)$

可以用原根 $g=7$ （ $g^{\frac{p-1}{3}}$ 即 $\omega_3^1$ ） 代替单位根然后大力二项式展开即可过

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const int N  = 5e5 + 50;
const ll mod = 19491001;
const ll g   = 7;
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
ll inv(ll a) {
    return qpow(a, mod - 2);
}
ll fac[N], ifac[N];
int n, k, d;
ll C(ll n, ll m) {
    return (fac[n] * ifac[m] % mod * ifac[n - m] % mod);
}
int main() {
    cin >> n >> k >> d;
    ll r   = qpow(g, (mod - 1) * inv(3) % mod);
    fac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    ifac[N - 1] = inv(fac[N - 1]);
    for (int i = N - 2; ~i; i--) {
        ifac[i] = ifac[i + 1] * (i + 1) % mod;
    }
    if (d == 1) {
        cout << qpow(k, n);
        return 0;
    } else if (d == 2) {
        ll ans = 0;
        for (int i = 0; i <= k; i++) {
            ans = (ans + C(k, i) * qpow(2 * i - k, n) % mod) % mod;
        }
        ans = (ans * inv(qpow(2, k) % mod) % mod);
        cout << ans << endl;
        return 0;
    } else {
        ll ans = 0;
        for (int i = 0; i <= k; i++) {
            int sum = 0;
            for (int j = 0; j <= k - i; j++) {
                sum = (sum + C(k - i, j) *
                                 qpow((r * r % mod * i % mod + r * j % mod + k -
                                       i - j + mod) %
                                          mod,
                                      n) %
                                 mod) %
                      mod;
            }
            ans = (ans + sum * C(k, i) % mod) % mod;
        }
        ans = (ans * inv(qpow(3, k) % mod) % mod);
        return cout << ans, 0;
    }
}
```

**Asusetic eru quionours**