### LOJ6538. 烷基计数 加强版 加强版

给出一个比较通用的计数方法

定义$Z(G)$为有限置换群$G$的循环指标，$Z(G)=\frac{1}{|G|}\sum\limits_{g\in G}\prod\limits_rs_r^{c_r(g)}$，这是一个关于$s_i$的多项式

$c_r(g)$是$g$的循环分解中有$r$个元素的循环数，也就是将$g$循环分解加起来

比如$Z(S_3)=\frac{1}{6}(2s_3+3s_2s_1+s_1^3)$ (如果考虑手性就是群$\mathfrak{A}_3$)

而如果我们把$s_i$用多项式$\mathbb{Z}[x^r]$代替就是$Z(S_3,F(x))=\frac{1}{6}(2F(x^3)+3F(x^2)F(x)+F^3(x))$  (不懂为啥能这么搞，也找不到相关资料

考虑烷基计数

拆去第一个碳原子，剩下的取代基可以自由分配，所以其生成函数$F(x)=1+xZ(s_3,F(X))=1+\frac{x}{6}[2F(x^3)+3F(x^2)F(x)+F^3(x)]$

可以分治NTT或者牛顿迭代

选择不用脑子的牛顿迭代

$G(F(X))=1+\frac{x}{6}[2F(x^3)+3F(x^2)F(x)+F^3(x)]-F(x)$

设已经求出$H(x)$满足$G(H(x))\equiv0\pmod{ x^{\frac{n}{2}}}$

那么$F(x)=H(x)-\frac{G(H(x))}{G'(H(x))}$

$G'(H(x))$中因为已知可以当作常数$G'(H(x))=x\frac{3H(x)^2+3H(x^2)}{6}-1$

带入$F(X)=H(x)-\frac{6-x(H(x)^3+3H(x^2)H(x)+2H(x^3))-6H(x)}{3x(H(x)^2+H(x^2))-6}$

```cpp
#include <algorithm>
// #include <dbg>
#include <iostream>
#include <vector>
using namespace std;
namespace Poly {
typedef long long ll;
const ll mod = 998244353;
const ll G = 3, invG = 332748118;
typedef vector<ll> poly;
const int N = 4e6 + 15;
int rev[N];
ll qpow(ll a, int b) {
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
void NTT(poly &a, int len, int typ) {
    a.resize(len);
    int lim = a.size();
    for (int i = 0; i < lim; i++) {
        if (i < rev[i]) {
            swap(a[i], a[rev[i]]);
        }
    }
    for (int mid = 1; mid < lim; mid *= 2) {
        ll wn = qpow(typ == 1 ? G : invG, (mod - 1) / (mid * 2));
        for (int j = 0; j < lim; j += mid * 2) {
            ll w = 1;
            for (int k = 0; k < mid; k++) {
                ll x = a[j + k], y = w * a[j + k + mid] % mod;
                a[j + k]       = (x + y) % mod;
                a[j + k + mid] = (x - y + mod) % mod;
                w              = w * wn % mod;
            }
        }
    }
    if (typ == 1) {
        return;
    }
    int invdeg = qpow(lim, mod - 2);
    for (int i = 0; i < lim; i++) {
        a[i] = a[i] * invdeg % mod;
    }
}
ll W[N];
void prework(int n) {
    for (int i = 1; i < n; i <<= 1) {
        W[i]  = 1;
        int w = qpow(3, (mod - 1) / (i * 2));

        for (int j = 1; j < i; j++)
            W[i + j] = (ll)W[i + j - 1] * w % mod;
    }
}

int getLen(int deg) {
    int len = 1;
    while (len < deg) {
        len *= 2;
    }
    return len;
}
void getRev(int deg) {
    for (int i = 0; i < deg; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (deg >> 1) : 0);
    }
}
int PrepareNTT(int deg) {
    int L = getLen(deg);
    getRev(L);
    return L;
}
poly _mul(const poly &a, const poly &b) {
    int len = a.size();
    poly res(len);
    for (int i = 0; i < len; i++) {
        res[i] = a[i] * b[i] % mod;
    }
    return res;
}
poly operator-(const poly &a) {
    int len = a.size();
    poly res(len);
    for (int i = 0; i < len; i++) {
        res[i] = (mod - a[i]) % mod;
    }
    return res;
}
poly operator+(const poly &a, const poly &b) {
    int len = a.size();
    poly res(len);
    for (int i = 0; i < len; i++) {
        res[i] = a[i] + b[i] % mod;
    }
    return res;
}
poly operator-(const poly &a, const poly &b) {
    return a + -b;
}
poly inv(poly a) {
    poly res, inv_a;
    res.resize(1);
    res[0]  = qpow(a[0], mod - 2);
    int lim = getLen(a.size());
    for (int len = 2; len <= lim; len *= 2) {
        int n = PrepareNTT(len + len);
        inv_a = a;
        inv_a.resize(n);
        res.resize(n);
        for (int i = len; i < n; i++) {
            inv_a[i] = 0;
        }
        NTT(inv_a, n, 1);
        NTT(res, n, 1);
        for (int i = 0; i < n; i++) {
            res[i] = 1ll * (2ll - 1ll * inv_a[i] * res[i] % mod + mod) % mod *
                     res[i] % mod;
        }
        NTT(res, n, -1);
        for (int i = len; i < n; i++) {
            res[i] = 0;
        }
    }
    res.resize(a.size());
    return res;
}
} // namespace Poly
using namespace Poly;
ll solve(int n) {
    poly c(1, 1), hx2, hx3, p, q;
    for (int len = 1; len < n; len *= 2) {
        hx2 = hx3 = poly(len * 2);
        for (int j = 0; j < len; j++)
            hx2[j << 1] = c[j];
        for (int j = 0; j * 3 < 2 * len; j++)
            hx3[j * 3] = c[j];
        PrepareNTT(len * 4);
        NTT(c, len * 4, 1);
        NTT(hx2, len * 4, 1);
        NTT(hx3, len * 4, 1);
        p = q = poly(len * 4);
        for (int j = 0; j < (len * 4); j++) {
            int w = j < (len * 2) ? W[len * 2 | j] : mod - W[len * 2 | j];
            q[j] =
                (3ll * w * ((ll(c[j]) * c[j] % mod + hx2[j]) % mod) + mod - 6) %
                mod;
            p[j] = (w *
                        ((ll(c[j]) * c[j] % mod * c[j] +
                          3ll * hx2[j] * c[j] % mod + 2ll * hx3[j]) %
                         mod) %
                        mod +
                    (mod - 6ll) * c[j] % mod + 6ll) %
                   mod;
        }

        NTT(p, len * 4, -1);
        NTT(q, len * 4, -1);
        q.resize(len * 2);
        q = inv(q);
        p.resize(len * 2);
        NTT(p, len * 4, 1);
        NTT(q, len * 4, 1);
        for (int j = 0; j < (len * 4); j++) {
            c[j] = (c[j] + (mod - p[j]) * (ll)q[j]) % mod;
        }
        NTT(c, len * 4, -1);
        c.resize(len * 2);
    }
    return c[n - 1];
}
int n;
poly res;
int main() {
    prework(2e6 + 10);
    cin >> n;
    cout << solve(n + 1);
    return 0;
}
```

