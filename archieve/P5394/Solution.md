### P5394 【模板】下降幂多项式乘法

暴力转一般多项式乘起来是$O(n\log^2 n)$的，会T

考虑点值多项式的EGF，$F_d=\sum \frac{F(i)}{i!}x^i$

对于单个的下降幂$x^\underline{n}$，它的点值EGF为$\large\sum\frac{i^{\underline{n}}}{i!}x^i=\sum\frac{1}{(1-n)!}x^i=x^n\sum\frac{1}{i!}x^i=e^xx^n$

$\large F(n)=\sum F[i]n^{\underline{i}}$

$\large F_d=\sum\frac{F(i)}{i!}x^i=\sum\frac{x^i}{i!}\sum F[j]i^{\underline{j}}$

$\large=\sum F[j]\sum\frac{i^{\underline{j}}}{i!}x^i=e^x\sum F[i]x^i$

也就是当作普通多项式卷$e^x$就能得到点值表达式，然后乘$e^{-x}$还原

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const ll G = 3, invG = 332748118;
const int N = 6e5 + 5;
int rev[N];
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
int getLen(int deg) {
    int len = 1;
    while (len < deg) {
        len *= 2;
    }
    for (int i = 0; i < len; i++) {
        rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
    }
    return len;
}
ll inv[N], fac[N];
void init(int lim) {
    inv[1] = inv[0] = fac[0] = 1;
    for (int i = 1; i <= lim; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    for (int i = 2; i <= lim; i++) {
        inv[i] = inv[mod % i] * (mod - mod / i) % mod;
    }
    for (int i = 2; i <= lim; i++) {
        inv[i] = inv[i] * inv[i - 1] % mod;
    }
}
void NTT(ll *f, int lim, int type) {
    for (int i = 0; i < lim; i++) {
        if (rev[i] < i) {
            swap(f[i], f[rev[i]]);
        }
    }
    for (int mid = 1; mid < lim; mid *= 2) {
        ll wn = qpow(type == 1 ? G : invG, (mod - 1) / (mid * 2));
        for (int j = 0; j < lim; j += mid * 2) {
            ll w = 1;
            for (int k = 0; k < mid; k++) {
                ll x = f[j + k], y = w * f[j + k + mid] % mod;
                f[j + k]       = (x + y) % mod;
                f[j + k + mid] = (x - y + mod) % mod;
                w              = w * wn % mod;
            }
        }
    }
}
ll s[N];
void _mul(ll *f, ll *g, int len) {
    for (int i = 0; i < len; i++) {
        f[i] = f[i] * s[i] % mod;
    }
}
void FDT(ll *f, int lim, int type) {
    if (type == 1) {
        for (int i = 0; i < lim; i++) {
            s[i] = inv[i];
        }
    } else {
        for (int i = 0; i < lim; i++) {
            s[i] = (i & 1 ? (mod - inv[i]) : inv[i]);
        }
    } // e^x / e^(-x)
    int len = getLen(lim * 2);
    for (int i = lim; i < len; i++) {
        s[i] = 0;
    }
    NTT(f, len, 1);
    NTT(s, len, 1);
    _mul(f, s, len);
    NTT(f, len, -1);
    ll invd = qpow(len, mod - 2);
    for (int i = 0; i < lim; i++) {
        f[i] = f[i] * invd % mod;
    }
    for (int i = lim; i < len; i++) {
        f[i] = 0;
    }
}
ll f[N], g[N];
int n, m;
int main() {
    cin >> n >> m;
    n++, m++;
    for (int i = 0; i < n; i++) {
        cin >> f[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> g[i];
    }
    int lim = n + m - 1;
    init(lim);
    FDT(f, lim, 1);
    FDT(g, lim, 1);
    for (int i = 0; i < lim; i++) {
        f[i] = f[i] * g[i] % mod * fac[i] % mod;
    }
    FDT(f, lim, 0);
    for (int i = 0; i < lim; i++) {
        cout << f[i] << " ";
    }
    return 0;
}
```