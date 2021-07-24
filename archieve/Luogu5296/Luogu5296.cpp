#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll     = long long;
const ll mod = 998244353;
const int N  = 35;
int n, k;
ll fac[N], ifac[N];
namespace Polynomial {
struct Poly {
    vector<ll> poly;
    int deg;
    Poly() {
        deg = -1;
    }
    Poly(int deg) : deg(deg), poly(deg + 1, 0) {
    }
    auto &operator[](const int &x) {
        return poly[x];
    }
    const auto &operator[](const int &x) const {
        return poly[x];
    }
    Poly operator+(const Poly &p) {
        Poly res(max(p.deg, deg));
        for (int i = 0; i <= max(p.deg, deg); i++) {
            if (i > deg) {
                res[i] = p[i] % mod;
            } else if (i > p.deg) {
                res[i] = poly[i] % mod;
            } else {
                res[i] = (p[i] + poly[i]) % mod;
            }
        }
        return res;
    }
    Poly operator-(const Poly &p) {
        Poly res(max(p.deg, deg));
        for (int i = 0; i <= max(p.deg, deg); i++) {
            if (i > deg) {
                res[i] = (mod - p[i]) % mod;
            } else if (i > p.deg) {
                res[i] = poly[i] % mod;
            } else {
                res[i] = (poly[i] - p[i] + mod) % mod;
            }
        }
        return res;
    }
    Poly operator*(const Poly &p) {
        Poly res(k);
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j <= i; j++) {
                res[i] = (res[i] + 1ll * poly[j] * p[i - j] % mod) % mod;
            }
        }
        return res;
    }
};
ostream &operator<<(ostream &out, const Poly &p) {
    for (int i = 0; i <= p.deg; i++) {
        out << p[i] << " ";
    }
    return out;
}
Poly Exp(ll w) {
    Poly res(k);
    ll qw = 1;
    for (int i = 0; i <= k; i++) {
        res[i] = qw * ifac[i] % mod;
        qw     = qw * w % mod;
    }
    return res;
}
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
Poly Inv(const Poly &p) {
    Poly res(k);
    res[0] = qpow(p[0], mod - 2);
    for (int i = 1; i <= k; i++) {
        ll nya = 0;
        for (int j = 0; j < i; j++) {
            nya = (nya + res[j] * p[i - j] % mod) % mod;
        }
        res[i] = (mod - nya) * res[0] % mod;
    }
    return res;
}
} // namespace Polynomial
using namespace Polynomial;
struct Matrix {
    vector<vector<Poly>> arr;
    int n;
    Matrix() {
    }
    Matrix(int n) {
        this->n = n;
        arr     = vector<vector<Poly>>(n, vector<Poly>(n));
    }
    auto &operator[](const int x) {
        return arr[x];
    }
};
void output(Matrix &L) {
    for (int i = 0; i < L.n; i++) {
        for (int j = 0; j < L.n; j++) {
            cout << L[i][j] << "|";
        }
        cout << endl;
    }
    cout << "---------------" << endl;
}
Poly det(Matrix M) {
    Poly res(k);
    res[0] = 1;
    int n  = M.n;
    for (int i = 0; i < n; i++) {
        res        = res * M[i][i];
        auto &&tmp = Inv(M[i][i]);
        for (int j = i; j < n; j++) {
            M[i][j] = M[i][j] * tmp;
        }
        for (int j = i + 1; j < n; j++) {
            auto tmp = M[j][i];
            for (int k = i; k < n; k++) {
                M[j][k] = M[j][k] - tmp * M[i][k];
            }
        }
    }
    return res;
}
int main() {
    cin >> n >> k;
    Matrix L(n);
    fac[0] = fac[1] = ifac[1] = ifac[0] = 1;
    for (int i = 2; i < N; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    ifac[N - 1] = qpow(fac[N - 1], mod - 2);
    for (int i = N - 2; i >= 2; i--) {
        ifac[i] = ifac[i + 1] * (i + 1) % mod;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int w;
            cin >> w;
            if (i >= j)
                continue;
            auto tmp = Exp(w);
            L[i][j]  = L[i][j] - tmp;
            L[j][i]  = L[j][i] - tmp;
            L[i][i]  = L[i][i] + tmp;
            L[j][j]  = L[j][j] + tmp;
        }
    }
    L.n = n - 1;
    cout << (fac[k] * det(L)[k] % mod) % mod << endl;
}
// Asusetic eru quionours
