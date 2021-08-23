#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
namespace FWT {
int getLen(int len) {
    int L = 1;
    while (L < len) {
        L *= 2;
    }
    return L;
}
void FWT(vector<ll> &f, int typ) {
    int lim = getLen(f.size());
    f.resize(lim);
    for (int mid = 1; mid < lim; mid *= 2) {
        for (int i = 0; i < lim; i += mid * 2) {
            for (int j = 0; j < mid; j++) {
                auto x = f[i + j], y = f[i + j + mid];
                if (typ == 1) {
                    f[i + j] = (x + y) % mod;
                } else {
                    f[i + j] = (x - y + mod) % mod;
                }
            }
        }
    }
}
} // namespace FWT
vector<ll> f(1000006);
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
int n;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        f[x]++;
    }
    int lim = FWT::getLen(f.size());
    f.resize(lim);
    f[lim - 1] = n;
    FWT::FWT(f, 1);
    for (int i = 0; i < lim; i++) {
        int x = (f[i] - n + mod) % mod;
        f[i] = qpow(2, x);
    }
    FWT::FWT(f, -1);
    cout << f[0] << endl;
    return 0;
}
// Asusetic eru quionours