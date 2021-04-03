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