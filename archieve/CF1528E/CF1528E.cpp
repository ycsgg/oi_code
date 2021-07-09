#include <array>
#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

const ll mod = 998244353;
struct modint {
    ll val;
    modint(ll v) : val(v) {
    }
    modint() {
        val = 0;
    }
    modint(const modint &b) {
        val = b.val % mod;
    }
    modint &operator=(ll v) {
        val = v % mod;
        return *this;
    }
    modint &operator=(const modint &b) {
        val = b.val;
        return *this;
    }
    modint operator+(const ll &b) const {
        return modint((b + val) % mod);
    }
    modint operator+(const modint &b) const {
        return modint((b.val + val) % mod);
    }
    modint operator-(const ll &b) const {
        return modint((mod + val - b) % mod);
    }
    modint operator-(const modint &b) const {
        return modint((mod + val - b.val) % mod);
    }
    modint operator*(const ll &b) const {
        return modint((b * val) % mod);
    }
    modint operator*(const modint &b) const {
        return modint((b.val * val) % mod);
    }
};
const int N = 1e6 + 10;
const modint inv2(499122177ll);
const modint inv6(166374059ll);
int n;
modint f[N], sum[N];
modint C2(const modint &x) {
    return x * (x - 1) * inv2;
}
modint C3(const modint &x) {
    return x * (x - 1) * (x - 2) * inv6;
}
int main() {
    cin >> n;
    f[0]   = 1;
    f[1]   = 2;
    sum[0] = 1;
    sum[1] = 3;
    for (int i = 2; i <= n; i++) {
        f[i]   = f[i - 1] + f[i - 1] * sum[i - 2] + C2(f[i - 1] + 1);
        sum[i] = sum[i - 1] + f[i];
    }
    modint ans = (f[n] * 2ll - 1);
    if (n >= 1) {
        ans = ans + C3(f[n - 1] + 2) * 2;
    }
    if (n >= 2) {
        ans = ans +
              (f[n - 1] * C2(sum[n - 2] + 1) + sum[n - 2] * C2(f[n - 1] + 1)) *
                  2ll;
    }
    for (int i = 0; i < n; i++) {
        ans = ans + (f[i] - 1) *
                        ((n - i - 1 >= 1) ? (f[n - i - 1] - f[n - i - 2]) : 0);
    }
    cout << ans.val << endl;
}
// Asusetic eru quionours
