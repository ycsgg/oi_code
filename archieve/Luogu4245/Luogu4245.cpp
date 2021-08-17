#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
using f80 = long double;
using ll = long long;
const f80 PI = acos(-1);
const int MAXL = 5e6;
struct complex {
    f80 real, img;
    complex() : real(0), img(0) {
    }
    complex(f80 real, f80 img) : real(real), img(img) {
    }
    complex conj() {
        return complex(real, -img);
    }
    complex operator+(complex rhs) const {
        return complex(real + rhs.real, img + rhs.img);
    }
    complex operator-(complex rhs) const {
        return complex(real - rhs.real, img - rhs.img);
    }
    complex operator*(complex rhs) const {
        return complex(real * rhs.real - img * rhs.img,
                       img * rhs.real + real * rhs.img);
    }
    complex operator*=(complex rhs) {
        return (*this) = (*this) * rhs;
    }
    friend complex operator*(f80 x, complex cp) {
        return complex(x * cp.real, x * cp.img);
    }
    complex operator/(f80 x) const {
        return complex(real / x, img / x);
    }
    complex operator/=(f80 x) {
        return (*this) = (*this) / x;
    }
    friend complex operator/(f80 x, complex cp) {
        return x * cp.conj() / (cp.real * cp.real - cp.img * cp.img);
    }
    complex operator/(complex rhs) const {
        return (*this) * rhs.conj() / (rhs.real * rhs.real - rhs.img * rhs.img);
    }
    complex operator/=(complex rhs) {
        return (*this) = (*this) / rhs;
    }
    f80 length() {
        return sqrt(real * real + img * img);
    }
};
/*complex omega(int len, bool typ) {
    return typ == 1 ? complex(cos(2 * PI / len), sin(2 * PI / len))
                    : complex(cos(2 * PI / len), -sin(2 * PI / len));
}*/
int rev[MAXL];
template <typename T>
int getLen(const vector<T> &poly) {
    int L = 1;
    while (L < poly.size()) {
        L *= 2;
    }
    return L;
}
int getLen(const int len) {
    int L = 1;
    while (L < len) {
        L *= 2;
    }
    return L;
}
void getRev(int n) {
    for (int i = 0; i < n; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    }
}
int Prepare(vector<complex> &poly) {
    int L = getLen(poly);
    poly.resize(L);
    getRev(L);
    return L;
}
vector<complex> omega{complex(0, 0), complex(1, 0)};
void FFT(vector<complex> &poly, int typ) {
    int lim = Prepare(poly);
    if (omega.size() < lim) {
        int k = __builtin_ctz(omega.size());
        omega.resize(lim);
        while ((1 << k) < lim) {
            double d = PI / double(1 << k);
            complex w(cos(d), sin(d));
            for (int i = 1 << (k - 1); i < (1 << k); ++i) {
                omega[i * 2] = omega[i];
                omega[i * 2 + 1] = omega[i] * w;
            }
            ++k;
        }
    }
    for (int i = 0; i < lim; i++) {
        if (rev[i] > i) {
            swap(poly[i], poly[rev[i]]);
        }
    }
    for (int mid = 1; mid < lim; mid *= 2) {
        for (int i = 0; i < lim; i += mid * 2) {
            for (int j = 0; j < mid; j++) {
                auto x = poly[i + j];
                auto y = poly[i + j + mid] * omega[j + mid];
                poly[i + j] = (x + y);
                poly[i + j + mid] = (x - y);
            }
        }
    }
    if (typ == -1) {
        for (int i = 0; i < lim; i++) {
            poly[i] /= lim;
        }
    }
}
auto _mul(vector<int> &f, vector<int> &g, int mod) {
    int lim = getLen(f.size() + g.size() - 1);
    static vector<complex> A(lim), B(lim), C(lim), D(lim);
    for (int i = 0; i < f.size(); i++) {
        A[i] = complex(f[i] >> 15, f[i] & 0x7fff);
    }
    for (int i = 0; i < g.size(); i++) {
        C[i] = complex(g[i] >> 15, g[i] & 0x7fff);
    }
    FFT(A, 1);
    FFT(C, 1);
    for (int i = 0; i < lim; i++) {
        B[i] = A[i].conj();
    }
    reverse(B.begin() + 1, B.end());
    for (int i = 0; i < lim; i++) {
        D[i] = C[i].conj();
    }
    reverse(D.begin() + 1, D.end());
    for (int i = 0; i < lim; i++) {
        auto aa = (A[i] + B[i]) * complex(0.5, 0);
        auto bb = (A[i] - B[i]) * complex(0, -0.5);
        auto cc = (C[i] + D[i]) * complex(0.5, 0);
        auto dd = (C[i] - D[i]) * complex(0, -0.5);
        A[i] = aa * cc + complex(0, 1) * (aa * dd + bb * cc);
        B[i] = bb * dd;
    }
    FFT(A, -1);
    FFT(B, -1);
    std::vector<int> res(lim);
    for (int i = 0; i < lim; ++i) {
        int t1 = (long long)(A[i].real + 0.5) % mod;
        int t2 = (long long)(A[i].img + 0.5) % mod;
        int t3 = (long long)(B[i].real + 0.5) % mod;
        res[i] = (((1ll << 30) * t1 + (1ll << 15) * t2 + t3) % mod + mod) % mod;
    }
    reverse(res.begin() + 1, res.end());
    res.resize(f.size() + g.size() - 1);
    return res;
}
int n, m, mod;
int main() {
    cin >> n >> m >> mod;
    vector<int> f(n + 1), g(m + 1);
    for (int i = 0; i <= n; i++) {
        cin >> f[i];
        f[i] %= mod;
    }
    for (int i = 0; i <= m; i++) {
        cin >> g[i];
        g[i] %= mod;
    }
    auto &&poly = _mul(f, g, mod);
    for (auto &v : poly) {
        cout << v % mod << " ";
    }
    return 0;
}
// Asusetic eru quionours