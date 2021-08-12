#include <array>
#include <iostream>
#include <vector>
using namespace std;
#define int ll
namespace FWT {
using ll = long long;
const ll mod = 998244353;
ll qpow(ll a, ll b) {
    b %= mod - 1;
    if (b < 0) {
        b += mod - 1;
    }
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
int getLen(int len) {
    int L = 1;
    while (L < len) {
        L *= 2;
    }
    return L;
}
int getLen(vector<ll> &f) {
    int len = 1;
    while (len < f.size()) {
        len *= 2;
    }
    return len;
}
ll inv(ll x) {
    return qpow(x, -1);
}
void FWT(vector<ll> &f, int type) {
    int lim = getLen(f);
    f.resize(lim);
    for (int mid = 1; mid < lim; mid *= 2) {
        for (int i = 0; i < lim; i += mid * 2) {
            for (int j = 0; j < mid; j++) {
                auto x = f[i + j], y = f[i + j + mid];
                f[i + j] = (x + y) % mod;
                f[i + j + mid] = (x - y + mod) % mod;
            }
        }
    }
    if (type == -1) {
        auto invdeg = inv(lim);
        for (int i = 0; i < lim; i++) {
            f[i] = f[i] * invdeg % mod;
        }
    }
}
} // namespace FWT
using ll = long long;
using FWT::mod;
int SG(int x) {
    int len = 1, sum = 0;
    while (sum < x) {
        sum += len;
        if (sum >= x)
            return x - (sum - len);
        len <<= 1;
    }
}
int v, m;
void mul(vector<ll> &res, vector<ll> &b) {
    for (int i = 0; i < res.size(); i++) {
        res[i] = res[i] * b[i] % mod;
    }
}
auto qpow(vector<ll> f, int b) {
    vector<ll> res(1000001);
    res[0] = 1;
    FWT::FWT(f, 1);
    FWT::FWT(res, 1);
    while (b) {
        if (b & 1) {
            mul(res, f);
        }
        mul(f, f);
        b /= 2;
    }
    FWT::FWT(res, -1);
    return res;
}
vector<ll> f(1000001);
signed main() {
    cin >> v >> m;
    for (int i = 1; i <= m; i++) {
        f[SG(i)]++;
    }
    f = qpow(f, v);
    ll ans = 0;
    for (int i = 1; i < f.size(); i++) {
        ans = (ans + f[i]) % mod;
    }
    cout << ans;
    return 0;
}
// Asusetic eru quionours