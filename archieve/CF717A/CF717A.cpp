#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
ll Add(ll x, ll y) {
    return (x + y) % mod;
}
ll Mul(ll x, ll y) {
    return x * y % mod;
}
ll Dec(ll x, ll y) {
    return (x - y + mod) % mod;
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
struct Zp {
    const static ll ItI = 5;
    ll a, b;
    Zp(ll a = 0, ll b = 0) {
        this->a = a;
        this->b = b;
    }
    Zp operator+(const ll x) const {
        return Zp(Add(a, x), b);
    }
    Zp operator-(const ll x) const {
        return Zp(Dec(a, x), b);
    }
    Zp operator*(const ll x) const {
        return Zp(Mul(a, x), Mul(b, x));
    }
    Zp operator+(const Zp &k) const {
        return Zp(Add(a, k.a), Add(b, k.b));
    }
    Zp operator-(const Zp &k) const {
        return Zp(Dec(a, k.a), Dec(b, k.b));
    }
    Zp operator*(const Zp &k) const {
        Zp res;
        res.a = (a * k.a + b * k.b * ItI) % mod;
        res.b = (a * k.b + b * k.a) % mod;
        return res;
    }
    friend Zp operator/(const Zp &x, const Zp &y) {
        Zp res, z = y;
        if (z.b != 0)
            z.b = mod - z.b;
        res = x * z;
        return res * qpow(Dec(y.a * y.a % mod, y.b * y.b * ItI % mod), mod - 2);
    }
};
Zp qpow(Zp a, ll b) {
    Zp res(1, 0);
    while (b) {
        if (b & 1) {
            res = res * a;
        }
        a = a * a;
        b /= 2;
    }
    return res;
}
Zp sum(Zp q, ll n) {
    return (qpow(q, n + 1) - q) / (q - 1);
}
Zp calc(Zp q, ll l, ll r) {
    if (q.a == 1 && q.b == 0)
        return q * (r - l + 1);
    return sum(q, r) - sum(q, l - 1);
}
const ll K = 201;
ll C[K][K], s[K][K], fac[K], inv[K];
ll l, r, k, ans;
ll solve() {
    ll res = 0;
    Zp td2, td1, A, B, x, y;
    A = Zp(0, inv[5]);
    B = Zp(0, mod - inv[5]);
    x = Zp(inv[2], inv[2]);
    y = Zp(inv[2], mod - inv[2]);
    for (int i = 0; i <= k; ++i) {
        td1 = Zp(0, 0);
        for (int j = 0; j <= i; ++j) {
            td2 = qpow(A, j) * qpow(B, i - j) *
                  calc(qpow(x, j) * qpow(y, i - j), l, r) * C[i][j];
            td1 = td1 + td2;
        }
        td1 = td1 * s[k][i];
        res = Add(res, td1.a);
    }
    res = res * qpow(fac[k], mod - 2) % mod;
    return res;
}
int main() {
    fac[0] = fac[1] = inv[1] = 1;
    for (int i = 2; i < K; ++i) {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    }
    C[0][0] = s[0][0] = 1;
    for (int i = 1; i < K; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
            C[i][j] = Add(C[i - 1][j], C[i - 1][j - 1]);
    }
    for (int i = 0; i < K - 1; ++i)
        for (int j = 1; j <= i + 1; ++j)
            s[i + 1][j] = Dec(s[i][j - 1], i * s[i][j] % mod);
    cin >> k >> l >> r;
    l += 2, r += 2;
    cout << solve();
    return 0;
}