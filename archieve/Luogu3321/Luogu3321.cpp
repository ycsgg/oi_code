#include <array>
#include <assert.h>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e6 + 10;
namespace RawNTT {
using ll = long long;
const ll mod = 1004535809;
const ll G = 3;
const ll invG = 334845270;
int rev[N];
int getLen(int n) {
    int L = 1;
    while (L <= n) {
        L *= 2;
    }
    return L;
}
void getRev(int n) {
    for (int i = 0; i < n; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    }
}
int Prepare(int x) {
    int L = getLen(x);
    getRev(L);
    return L;
}
ll qpow(ll a, ll b, ll mod = 1004535809ll) {
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
void NTT(vector<ll> &f, int typ) {
    int lim = f.size();
    for (int i = 0; i < lim; i++) {
        if (i < rev[i]) {
            swap(f[i], f[rev[i]]);
        }
    }
    for (int mid = 1; mid < lim; mid *= 2) {
        ll wn = qpow(typ == 1 ? G : invG, (mod - 1) / (mid * 2));
        for (int i = 0; i < lim; i += mid * 2) {
            ll w = 1;
            for (int j = 0; j < mid; j++) {
                ll x = f[i + j], y = f[i + j + mid] * w % mod;
                f[i + j] = (x + y) % mod;
                f[i + j + mid] = (x - y + mod) % mod;
                w = w * wn % mod;
            }
        }
    }
    if (typ == 1) {
        return;
    }
    auto invdeg = qpow(lim, mod - 2);
    for (int i = 0; i < lim; i++) {
        f[i] = f[i] * invdeg % mod;
    }
}
} // namespace RawNTT
namespace Polynomial {
using namespace RawNTT;
struct Poly {
    vector<ll> poly;
    auto &operator[](const int x) {
        return poly[x];
    }
    auto &operator[](const int x) const {
        return poly[x];
    }
    auto deg() const {
        return poly.size();
    }
    friend Poly operator*(const Poly &A, const Poly &B) {
        Poly res;
        Poly tmpa = A, tmpb = B;
        int alen = A.deg(), blen = B.deg();
        int lim = Prepare(alen + blen);
        tmpa.poly.resize(lim);
        tmpb.poly.resize(lim);
        res.poly.resize(lim);
        NTT(tmpa.poly, 1);
        NTT(tmpb.poly, 1);
        for (int i = 0; i < lim; i++) {
            res[i] = (tmpa[i] * tmpb[i]) % mod;
        }
        NTT(res.poly, -1);
        res.poly.resize(alen + blen - 1);
        return res;
    }
};
Poly MulM(Poly A, Poly B, int m) {
    Poly res = A * B;
    int lim = res.deg();
    for (int i = lim - 1; i >= m - 1; i--) {
        res[i - m + 1] = (res[i - m + 1] + res[i]) % mod;
        res[i] = 0;
    }
    res.poly.resize(m);
    /*for (int i = 0; i < m; i++) {
        cout << res[i] << " ";
    }
    cout << endl;*/
    return res;
}
Poly PowM(Poly &A, int b, int m) {
    Poly res;
    res.poly.assign(m, 0);
    res[0] = 1;
    while (b) {
        if (b & 1) {
            res = MulM(res, A, m);
        }
        A = MulM(A, A, m);
        b /= 2;
    }
    return res;
}
} // namespace Polynomial
int q[1111], cnt;
int FindG(int m) {
    for (int i = 2; i <= m - 2; i++) {
        if ((m - 1) % i == 0) {
            q[++cnt] = i;
        }
    }
    int now = 2;
    while ("ycs") {
        bool flag = 1;
        for (int j = 1; j <= cnt && flag; j++) {
            if (RawNTT::qpow(now, q[j], m) == 1) {
                flag = 0;
            }
        }
        if (flag) {
            return now;
        }
        now++;
    }
    return -1;
}
using namespace Polynomial;
int n, m, x, S;
int lg[8080];
Poly f, g;
int main() {
    cin >> n >> m >> x >> S;
    int g = FindG(m);
    ll gp = 1;
    for (int i = 1; i <= m - 2; i++) {
        gp = gp * g % m;
        lg[gp] = i;
    }
    f.poly.resize(m);
    for (int i = 1; i <= S; i++) {
        int x;
        cin >> x;
        if (x) {
            f[lg[x]] = 1;
        }
    }
    f = PowM(f, n, m);
    cout << f[lg[x]] << endl;
    return 0;
}
// Asusetic eru quionours