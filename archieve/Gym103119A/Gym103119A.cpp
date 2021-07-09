#include <array>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
namespace Poly {
const int N = 2e6 + 5;
typedef long long ll;
static const ll mod  = 998244353;
static const ll G    = 3;
static const ll invG = 332748118;
long long inv[N], rev[N];
template <typename T> class Polynomial;
template <typename T> void NTT(Polynomial<T> &poly);
template <typename T> class Polynomial {
  private:
    typedef std::vector<T> Poly;
    typedef T (*funcptr)(int, T);
    static const int MAXN = 4e5 + 5;

  public:
    Poly a;
    int type;
    Polynomial();
    Polynomial(T *k, int len);
    Polynomial(int len);
    Polynomial(const Polynomial<T> &b);
    void add(T x);
    void erase(int pos);
    void init();
    Polynomial<T> operator+(const Polynomial<T> &b);
    Polynomial<T> operator-(const Polynomial<T> &b);
    Polynomial<T> operator*(const Polynomial<T> &b);
    Polynomial<T> operator+(const T &b);
    Polynomial<T> operator-(const T &b);
    Polynomial<T> operator*(const T &b);
    Polynomial<T> &operator=(const Polynomial<T> &b);
    Polynomial<T> &operator=(funcptr func);
    bool operator==(const Polynomial<T> &b);
    bool operator==(const T &b);
    T &operator[](const int &pos);
    T operator[](const int &pos) const;
    int len() const;
    void resize(int siz);
};
template <typename T> Polynomial<T> Inverse(Polynomial<T> poly);
template <typename T> Polynomial<T> Integral(Polynomial<T> poly);
template <typename T> Polynomial<T> Derivative(Polynomial<T> poly);
template <typename T> Polynomial<T> Ln(Polynomial<T> poly);
template <typename T> Polynomial<T> Exp(Polynomial<T> poly);
template <typename T> Polynomial<T> Sqrt(Polynomial<T> poly);
template <typename T> Polynomial<T> Pow(Polynomial<T> poly, long long k);
template <typename T> Polynomial<T> CompositionInverse(Polynomial<T> poly);

template <typename T> Polynomial<T> operator-(const Polynomial<T> &poly);
template <typename T>
Polynomial<T> operator-(const T &b, const Polynomial<T> &poly);
template <typename T>
Polynomial<T> operator+(const T &b, const Polynomial<T> &poly);
template <typename T>
Polynomial<T> operator/(const T &b, const Polynomial<T> &poly);
template <typename T>
Polynomial<T> operator*(const T &b, const Polynomial<T> &poly);

template <typename T>
std::ostream &operator<<(std::ostream &out, const Polynomial<T> &k) {
    int len = k.a.size();
    /*int now = 0;
    for (int i = 0; i < len; i++) {
        if (i == 0) {
            out << k[i];
        }
        if (i != 0 && k[i] != 0) {
            out << "+" << k[i] << "x^" << i;
        }
    }*/
    for (int i = 0; i < len; i++) {
        out << k[i] << " ";
    }
    return out;
}
template <typename T>
std::istream &operator>>(std::istream &in, Polynomial<T> &k) {
    int len = k.len();
    for (int i = 0; i < len; i++) {
        in >> k[i];
    }
    return in;
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
    for (int i = 0; i < n; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    }
}
int Pre_Transform(int len);
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
int getLen(int deg) {
    int len = 1;
    while (len < deg) {
        len *= 2;
    }
    return len;
}
} // namespace Poly
namespace Poly {

template <typename T> Polynomial<T>::Polynomial() {
    this->a.resize(100);
    this->type = 1;
}
template <typename T> Polynomial<T>::Polynomial(T *k, int len) {
    this->type = 1;
    this->a.resize(len + 1);
    for (int i = 0; i < len; i++) {
        a.push_back(k[i]);
    }
}
template <typename T> Polynomial<T>::Polynomial(int len) {
    this->type = 1;
    this->a.resize(len + 1);
}
template <typename T> Polynomial<T>::Polynomial(const Polynomial<T> &b) {
    this->type = b.type;
    a          = b.a;
}

template <typename T> void Polynomial<T>::add(T x) {
    this->a.push_back(x);
}
template <typename T> void Polynomial<T>::erase(int pos) {
    a[pos] = 0;
}
template <typename T> void Polynomial<T>::init() {
    this->a.clear();
}
template <typename T> int Polynomial<T>::len() const {
    return a.size();
}
template <typename T> void Polynomial<T>::resize(int siz) {
    this->a.resize(siz);
}

template <typename T> T &Polynomial<T>::operator[](const int &pos) {
    return a[pos];
}
template <typename T> T Polynomial<T>::operator[](const int &pos) const {
    if (pos >= a.size())
        return 0;
    return a[pos];
}
template <typename T> bool Polynomial<T>::operator==(const Polynomial<T> &b) {
    if (a.size() == b.size()) {
        int len = a.size();
        for (int i = 0; i < len; i++) {
            if (a[i] != b[i])
                return false;
        }
    } else {
        return false;
    }
    return true;
}
template <typename T> bool Polynomial<T>::operator==(const T &b) {
    if (this->a.size() == 1 && a[0] == b)
        return true;
    return false;
}
template <typename T>
Polynomial<T> Polynomial<T>::operator+(const Polynomial<T> &b) {
    int alen = a.size();
    int blen = b.len();
    int mlen = std::max(alen, blen), klen = std::min(alen, blen);
    Polynomial<T> res(mlen);
    for (int i = 0; i < klen; i++) {
        res[i] = (this->a[i] + b.a[i]) % mod;
    }
    if (alen < blen) {
        for (int i = alen; i < blen; i++) {
            res[i] = b.a[i] % mod;
        }
    } else {
        for (int i = blen; i < alen; i++) {
            res[i] = a[i] % mod;
        }
    }
    return res;
}
template <typename T> Polynomial<T> Polynomial<T>::operator+(const T &b) {
    Polynomial<T> res(this->len());
    res.a  = this->a;
    res[0] = (res[0] + b) % mod;
    return res;
}
template <typename T>
Polynomial<T> Polynomial<T>::operator-(const Polynomial<T> &b) {
    int alen = a.size();
    int blen = b.size();
    int mlen = std::max(alen, blen), klen = std::min(alen, blen);
    Polynomial<T> res(mlen);
    for (int i = 0; i < klen; i++) {
        res[i] = (this->a[i] - b.a[i] + mod) % mod;
    }
    if (alen < blen) {
        for (int i = alen; i < blen; i++) {
            res[i] = (mod - b.a[i]) % mod;
        }
    } else {
        for (int i = blen; i < alen; i++) {
            res[i] = (mod - a[i]) % mod;
        }
    }
    return res;
}
template <typename T> Polynomial<T> Polynomial<T>::operator-(const T &b) {
    Poly res(this);
    res[0] = (res[0] - b + mod) % mod;
    return res;
}
template <typename T>
Polynomial<T> &Polynomial<T>::operator=(const Polynomial<T> &b) {
    this->a.clear();
    a          = b.a;
    this->type = b.type;
    return *this;
}

template <typename T> Polynomial<T> Polynomial<T>::operator*(const T &b) {
    Polynomial<T> res(this->len());
    res.a   = a;
    int len = res.len();
    for (int i = 0; i < len; i++) {
        res[i] = (res[i] * b) % mod;
    }
    return res;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator*(const Polynomial<T> &b) {
    Polynomial<T> res;
    Polynomial<T> tmpa(*this), tmpb(b);
    if (type == b.type) {
        int alen = tmpa.len(), blen = tmpb.len();
        int lim = Pre_Transform((alen + blen));
        if (type == 1) {
            res.resize(lim);
            tmpa.resize(lim);
            tmpb.resize(lim);
            NTT(tmpa);
            NTT(tmpb);
        }
        for (int i = 0; i < lim; i++) {
            res[i] = (1ll * tmpa[i] * tmpb[i]) % mod;
        }
        res.type = -1;
        NTT(res);
        res.resize(alen + blen - 1);
        return res;
    }
    return b;
}

int Pre_Transform(int len) {
    int L = getLen(len);
    getRev(L);
    return L;
}
template <typename T> void NTT(Polynomial<T> &poly) {
    int lim = poly.len();
    for (int i = 0; i < lim; i++) {
        if (i < rev[i])
            std::swap(poly.a[i], poly.a[rev[i]]);
    }
    for (int mid = 1; mid < lim; mid *= 2) {
        ll wn = qpow(poly.type == 1 ? G : invG, (mod - 1) / (mid * 2));
        for (int j = 0; j < lim; j += mid * 2) {
            ll w = 1;
            for (int k = 0; k < mid; k++) {
                ll x = poly[j + k], y = w * poly[j + k + mid] % mod;
                poly[j + k]       = (x + y) % mod;
                poly[j + k + mid] = (x - y + mod) % mod;
                w                 = w * wn % mod;
            }
        }
    }
    if (poly.type == 1) {
        poly.type = -1;
        return;
    }
    poly.type = 1;
    ll invdeg = qpow(lim, mod - 2);
    for (int i = 0; i < lim; i++) {
        poly[i] = poly[i] * invdeg % mod;
    }
}

template <typename T> Polynomial<T> operator-(const Polynomial<T> &poly) {
    Polynomial<T> res(poly);
    for (int i = 0; i < res.len(); i++) {
        res[i] = (mod - res[i]) % mod;
    }
    return res;
}
template <typename T>
Polynomial<T> operator-(const T &b, const Polynomial<T> &poly) {
    return (-poly) + b;
}
template <typename T>
Polynomial<T> operator+(const T &b, const Polynomial<T> &poly) {
    return poly + b;
}
template <typename T>
Polynomial<T> operator*(const T &b, const Polynomial<T> &poly) {
    return poly * b;
}
template <typename T>
Polynomial<T> operator/(const T &b, const Polynomial<T> &poly) {
    return Inverse(poly) * b;
}

ll invx(ll x) {
    return qpow(x, mod - 2);
}

template <typename T> Polynomial<T> Inverse(Polynomial<T> poly) {
    Polynomial<T> res, inv_a;
    res.resize(1);
    res[0]  = invx(poly[0]);
    int lim = getLen(poly.len());
    for (int len = 2; len <= lim; len <<= 1) {
        int n = Pre_Transform(len + len);
        inv_a = poly;
        inv_a.resize(n);
        res.resize(n);
        for (int i = len; i < n; i++)
            inv_a[i] = 0;
        NTT(inv_a);
        NTT(res);
        for (int i = 0; i < n; i++) {
            res[i] = 1ll * (2ll - 1ll * inv_a[i] * res[i] % mod + mod) % mod *
                     res[i] % mod;
        }
        NTT(res);
        for (int i = len; i < n; i++) {
            res[i] = 0;
        }
    }
    res.resize(poly.len());
    return res;
}
template <typename T> Polynomial<T> Derivative(Polynomial<T> poly) {
    Polynomial<T> res(poly.len());
    for (int i = 1; i < poly.len(); i++) {
        res[i - 1] = 1ll * i * poly[i] % mod;
    }
    res[res.len() - 1] = 0;
    return res;
}
template <typename T> Polynomial<T> Integral(Polynomial<T> poly) {
    Polynomial<T> res(poly.len());
    for (int i = 1; i < poly.len(); i++) {
        res[i] = 1ll * invx(i) * poly[i - 1] % mod;
    }
    res[0] = 0;
    res.resize(poly.len());
    return res;
}
template <typename T> Polynomial<T> Ln(Polynomial<T> poly) {
    Polynomial<T> res;
    res = Derivative(poly) * Inverse(poly);
    res.resize(poly.len());
    return Integral(res);
}
template <typename T> Polynomial<T> Exp(Polynomial<T> poly) {
    Polynomial<T> res(1), d;
    int lim = getLen(poly.len());
    res[0]  = 1;
    for (int len = 2; len <= lim; len *= 2) {
        d = Ln(res);
        d.resize(len);
        d[0] = (1ll * poly[0] + 1ll - d[0] + mod) % mod;
        for (int i = 1; i < len; i++) {
            d[i] = (1ll * poly[i] - d[i] + mod) % mod;
        }
        int n = Pre_Transform(len + len);
        res.resize(n);
        d.resize(n);
        NTT(res);
        NTT(d);
        for (int i = 0; i < n; i++) {
            res[i] = 1ll * res[i] * d[i] % mod;
        }
        NTT(res);
        for (int i = len; i < (len * 2); i++) {
            res[i] = d[i] = 0;
        }
    }
    res.resize(poly.len());
    return res;
}
template <typename T> Polynomial<T> Sqrt(Polynomial<T> poly) {
    return Exp(Ln(poly) * invx(2));
}
template <typename T> Polynomial<T> Pow(Polynomial<T> poly, long long k) {
    return Exp(Ln(poly) * k);
}
template <typename T> Polynomial<T> CompositionInverse(Polynomial<T> poly) {
    Polynomial<T> ret, invc, pc;
    int n = poly.len();
    invc  = poly;
    ret.resize(n);
    pc.resize(n);
    pc[0] = 1;
    for (int i = 0; i < n - 1; i++)
        invc[i] = invc[i + 1];
    invc[n - 1] = 0;
    invc        = Inverse(invc);
    for (int i = 1; i < n; ++i) {
        pc = pc * invc;
        pc.resize(n);
        ret[i] = 1ll * pc[i - 1] * invx(i) % mod;
    }
    return ret;
}
} // namespace Poly
using namespace Poly;
Polynomial<ll> solve(int l, int r, vector<Polynomial<ll>> &v) {
    if (l == r) {
        return v[l];
    }
    if (r - l == 1) {
        return v[l] * v[r];
    }
    int mid   = (l + r) / 2;
    auto &&vl = solve(l, mid, v);
    auto &&vr = solve(mid + 1, r, v);
    return vl * vr;
}
int T, n;
ll fac[N], ifac[N];
int main() {
    cin >> T;
    fac[0] = 1;
    fac[1] = 1;
    for (int i = 2; i <= 100005; i++) {
        fac[i] = 1ll * i * fac[i - 1] % mod;
    }
    ifac[100005] = qpow(fac[100005], mod - 2);
    for (int i = 100004; i >= 1; i--) {
        ifac[i] = 1ll * (i + 1) * ifac[i + 1] % mod;
    }
    ifac[0] = 1;
    while (T--) {
        cin >> n;
        vector<Polynomial<ll>> v(n);
        for (int i = 0; i < n; i++) {
            v[i].resize(2);
            cin >> v[i][1];
            v[i][0] = 1;
        }
        ll ans     = 0;
        auto &&res = solve(0, n - 1, v);
        for (int i = 1; i <= n; i++) {
            ans = (ans + 1ll * fac[i] * res[i] % mod * fac[n - i]) % mod;
            ans %= mod;
        }
        cout << ans * ifac[n] % mod << endl;
    }
    return 0;
}
// Asusetic eru quionours