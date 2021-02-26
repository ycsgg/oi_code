#include <cstring>
#include <iostream>
#include <vector>
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
    typedef T (*funcptr)(int,T);
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