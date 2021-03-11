#include <iostream>
using namespace std;
int x1, yOOO_1, x2, yOOO_2, x3, y3, x4, y4, x5, y5, x6, y6;
namespace IO {
int f;
template <typename FirstVal> void read(FirstVal &v) {
    v               = 0;
    f               = 1;
    register char c = getchar();
    for (; !isdigit(c); c = getchar()) {
        if (c == '-') {
            f = -1;
        }
    }
    for (; isdigit(c); v = v * 10 + c - '0', c = getchar())
        ;
}
template <typename FirstVal, typename... RestVal>
void read(FirstVal &fst, RestVal &... s) {
    read(fst);
    read(s...);
}
} // namespace IO
using IO::read;
const int N         = 2e6;
const long long mod = 1e9 + 7;
typedef long long ll;
ll fac[N + 2], invfac[N + 2];
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
ll calc(int a, int b, int c, int d) {
    return 1ll * fac[abs(a - c) + abs(b - d)] * invfac[abs(a - c)] % mod *
           invfac[abs(b - d)] % mod;
}
ll C(ll n, ll m) {
    return 1ll * fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}
ll solve(ll x1, ll yOOO_1, ll sign1, ll x2, ll yOOO_2, ll sign2, ll x3, ll x4,
         ll y3, ll y4) {
    ll res = 0;
    for (ll x = x3; x <= x4; x++) {
        res = (res + 1ll * (x + y4 + 1) * C(x - x1 + y4 - yOOO_1, y4 - yOOO_1) % mod *
                         C(x2 - x + yOOO_2 - y4 - 1, yOOO_2 - y4 - 1) % mod);
        res = (res + mod -
               1ll * (x + y3) * C(x - x1 + y3 - yOOO_1 - 1, y3 - yOOO_1 - 1) % mod *
                   C(x2 - x + yOOO_2 - y3, yOOO_2 - y3) % mod);
    }
    for (ll y = y3; y <= y4; y++) {
        res = (res + 1ll * (y + x4 + 1) * C(y - yOOO_1 + x4 - x1, x4 - x1) % mod *
                         C(yOOO_2 - y + x2 - x4 - 1, x2 - x4 - 1) % mod);
        res = (res + mod -
               1ll * (y + x3) * C(y - yOOO_1 + x3 - x1 - 1, x3 - x1 - 1) % mod *
                   C(yOOO_2 - y + x2 - x3, x2 - x3) % mod);
    }
    res %= mod;
    return res * sign1 * sign2 % mod;
}
ll ans;
ll f[5][5], g[5][5];
void init() {
    f[0][0] = x1 - 1, f[0][1] = yOOO_1 - 1, f[0][2] = 1;
    f[1][0] = x2, f[1][1] = yOOO_1 - 1, f[1][2] = -1;
    f[2][0] = x1 - 1, f[2][1] = yOOO_2, f[2][2] = -1;
    f[3][0] = x2, f[3][1] = yOOO_2, f[3][2] = 1;

    g[0][0] = x5, g[0][1] = y5, g[0][2] = 1;
    g[1][0] = x6 + 1, g[1][1] = y5, g[1][2] = -1;
    g[2][0] = x5, g[2][1] = y6 + 1, g[2][2] = -1;
    g[3][0] = x6 + 1, g[3][1] = y6 + 1, g[3][2] = 1;
}
int main() {
    read(x1, x2, x3, x4, x5, x6, yOOO_1, yOOO_2, y3, y4, y5, y6);
    init();
    fac[0] = fac[1] = invfac[0] = invfac[1] = 1;
    for (int i = 2; i <= N; i++) {
        fac[i] = 1ll * fac[i - 1] * i % mod;
    }
    invfac[N] = qpow(fac[N], mod - 2);
    for (int i = N - 1; i >= 2; i--) {
        invfac[i] = 1ll * invfac[i + 1] * (i + 1) % mod;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ans += solve(f[i][0], f[i][1], f[i][2], g[j][0], g[j][1], g[j][2],
                         x3, x4, y3, y4);
            ans %= mod;
        }
    }
    cout << (ans + mod) % mod;
    return 0;
}