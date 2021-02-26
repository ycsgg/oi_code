#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
namespace Poly {
typedef long long ll;
const int N   = 4e5 + 5;
const ll mod  = 998244353;
const ll G    = 3;
const ll invG = 332748118;
ll qpow(ll a, ll b) {
    ll res = 1, base = a;
    while (b) {
        if (b & 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        b /= 2;
    }
    return res;
}
int rev[N];
ll inv[N];
template <typename T> void fill(T *a, int siz, int val = 0) {
    for (int i = 0; i < siz; i++) {
        a[i] = val;
    }
}
template <typename T> void fill(T *a, T *b, int siz) {
    for (int i = 0; i < siz; i++) {
        a[i] = b[i];
    }
}
void getInv(int n) {
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!inv[i]) {
            inv[i] = inv[mod % i] * (mod - mod / i) % mod;
        }
    }
}
void getRev(int n) {
    for (int i = 1; i < n; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    }
}
int getLen(int deg) {
    int len = 1;
    while (len < deg) {
        len *= 2;
    }
    return len;
}
void NTT(ll *a, int deg, int type) {
    int lim = getLen(deg);
    getRev(lim);
    for (int i = 0; i < lim; i++) {
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    }
    for (int mid = 1; mid < lim; mid *= 2) {
        ll wn = qpow(type == 1 ? G : invG, (mod - 1) / (mid * 2));
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
    if (type == 1)
        return;
    ll invdeg = qpow(lim, mod - 2);
    for (int i = 0; i < lim; i++) {
        a[i] = a[i] * invdeg % mod;
    }
}
void _mul(ll *a, ll *b, int len) {
    for (int i = 0; i < len; i++) {
        a[i] = (a[i] * b[i]) % mod;
    }
}
void Mul(ll *a, ll *b, int deg, int lim) {
    static ll tmp[N];
    int len = getLen(deg * 2);
    fill(tmp, len, 0);
    fill(tmp, b, deg);
    NTT(a, len, 1);
    NTT(tmp, len, 1);
    _mul(a, tmp, len);
    NTT(a, len, -1);
    fill(a + lim, len - lim, 0);
}
void Inv(ll *a, ll *b, int deg) {
    static ll ans[N], invc[N], tmpb[N];
    int lim = getLen(deg);
    fill(ans, lim * 2, 0);
    fill(invc, lim * 2, 0);
    fill(tmpb, lim * 2, 0);
    ans[0] = qpow(a[0], mod - 2);
    for (int len = 2; len <= lim; len *= 2) {
        for (int i = 0; i < (len / 2); i++) {
            invc[i] = 2ll * ans[i] % mod;
        }
        fill(tmpb, a, len);
        NTT(ans, len * 2, 1);
        NTT(tmpb, len * 2, 1);
        _mul(ans, ans, len * 2);
        _mul(ans, tmpb, len * 2);
        NTT(ans, len * 2, -1);
        fill(ans + len, len, 0);
        for (int i = 0; i < len; i++) {
            ans[i] = (invc[i] - ans[i] + mod) % mod;
        }
    }
    fill(b, ans, deg);
}
void D(ll *a, ll *b, int deg) {
    for (int i = 1; i < deg; i++) {
        b[i - 1] = a[i] * i % mod;
    }
    b[deg - 1] = 0;
}
void Int(ll *a, ll *b, int deg) {
    if (!inv[deg])
        getInv(deg);
    for (int i = deg; i >= 0; i--) {
        b[i] = a[i - 1] * inv[i] % mod;
    }
    b[0] = 0;
}
void Ln(ll *a, ll *b, int deg) {
    static ll tmpl[N], tmpk[N];
    fill(tmpl, a, deg * 2);
    D(tmpl, tmpl, deg);
    Inv(a, tmpk, deg);
    Mul(tmpk, tmpl, deg, deg);
    Int(tmpk, b, deg - 1);
    fill(tmpl, deg * 2);
    fill(tmpk, deg * 2);
}
void Exp(ll *a, ll *b, int deg) {
    static ll te[N], tk[N];
    int lim = getLen(deg);
    fill(te, deg * 2);
    fill(tk, deg * 2);
    te[0] = 1;
    for (int len = 2; len <= lim; len *= 2) {
        fill(tk, te, len / 2);
        Ln(tk, tk, len);
        for (int i = 0; i < len; i++) {
            tk[i] = (a[i] - tk[i] + mod) % mod;
        }
        tk[0] = (tk[0] + 1) % mod;
        Mul(te, tk, len, len);
    }
    fill(b, te, deg);
}
void Pow(ll *a, ll *b, ll k, int deg) {
    Ln(a, b, deg);
    for (int i = 0; i < deg; i++) {
        b[i] = b[i] * k % mod;
    }
    Exp(b, b, deg);
}
void Sqrt(ll *a, ll *b, int deg) {
    static ll b1[N], b2[N];
    int lim = getLen(deg);
    fill(b1, lim * 2);
    fill(b2, lim * 2);
    b1[0] = 1;
    for (int len = 2; len <= lim; len *= 2) {
        for (int i = 0; i < (len / 2); i++) {
            b2[i] = 2ll * b1[i] % mod;
        }
        Inv(b2, b2, len);
        NTT(b1, len, 1);
        _mul(b1, b1, len);
        NTT(b1, len, -1);
        for (int i = 0; i < len; i++) {
            b1[i] = (b1[i] + a[i]) % mod;
        }
        Mul(b1, b2, len, len);
    }
    fill(b, b1, deg);
}
} // namespace Poly
const int N = 4e5 + 5, mod = 998244353;
int n, m;
long long a[N], b[N];
int main() {
    cin >> n;
    for (int i = 0; i < n;i++){
        cin >> a[i];
    }
    Poly::Inv(a, b, n);
    for (int i = 0; i < n;i++){
        cout << b[i] << " ";
    }
}