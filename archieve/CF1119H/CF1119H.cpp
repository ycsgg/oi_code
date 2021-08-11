#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 998244353;
const int N = 1e5 + 10;
int getLen(const vector<ll> &f) {
    int len = 1;
    while (len < f.size()) {
        len *= 2;
    }
    return len;
}
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
        b /= 2;
    }
    return res;
}
void FWT(vector<ll> &f, int typ) {
    int lim = getLen(f);
    for (int mid = 1; mid < lim; mid *= 2) {
        for (int i = 0; i < lim; i += mid * 2) {
            for (int j = 0; j < mid; j++) {
                auto x = f[i + j], y = f[i + j + mid];
                f[i + j] = (x + y);
                f[i + j + mid] = (x - y);
            }
        }
    }
    if (typ == -1) {
        auto invdeg = qpow(lim, -1);
        for (int i = 0; i < lim; i++) {
            f[i] %= mod;
            f[i] = f[i] * invdeg % mod;
        }
    }
}
ll n, k;
ll a[N], b[N], c[N];
ll x, y, z;
ll all;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    k = (1 << k);
    cin >> x >> y >> z;
    vector<ll> FB(k), FC(k), FBC(k), F(k);
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i] >> c[i];
        all ^= a[i];
        b[i] ^= a[i];
        c[i] ^= a[i];
        FB[b[i]]++;
        FC[c[i]]++;
        FBC[b[i] ^ c[i]]++;
    }
    FWT(FB, 1);
    FWT(FC, 1);
    FWT(FBC, 1);
    ll q1 = (x + y + z) % mod;
    ll q2 = (x + y - z) % mod;
    ll q3 = (x - y + z) % mod;
    ll q4 = (x - y - z) % mod;
    for (int i = 0; i < k; i++) {
        ll c1 = (n + FB[i] + FC[i] + FBC[i]) / 4;
        ll c2 = (n + FB[i] - c1 * 2) / 2;
        ll c3 = (n + FC[i] - c1 * 2) / 2;
        ll c4 = (n + FBC[i] - c1 * 2) / 2;
        F[i] = qpow(q1, c1) * qpow(q2, c2) % mod * qpow(q3, c3) % mod *
               qpow(q4, c4) % mod;
    }
    FWT(F, -1);
    for (int i = 0; i < k; i++) {
        cout << (F[i ^ all] + mod) % mod << " ";
    }
    cout.flush();
    return 0;
}
// Asusetic eru quionours
