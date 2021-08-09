#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 998244353;
const int N = 1e6 + 10;
int n;
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
ll inv(ll x) {
    return qpow(x, -1);
}
int getLen(vector<ll> &f) {
    int len = 1;
    while (len < f.size()) {
        len *= 2;
    }
    return len;
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
vector<ll> f(1000005);
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        f[0]++;
        f[x] += 2;
    }
    FWT(f, 1);
    auto inv4 = inv(4);
    for (auto &v : f) {
        auto k = 1ll * (3 * n - v + mod) % mod * inv4 % mod;
        v = (k & 1) ? (mod - qpow(3, n - k)) : (qpow(3, n - k));
    }
    FWT(f, -1);
    cout << (f[0] - 1 + mod) % mod << endl;
    return 0;
}
// Asusetic eru quionours