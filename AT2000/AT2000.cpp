#include <iostream>
using namespace std;
const int N         = 2000 * 2000;
const long long mod = 1e9 + 7;
int n, k;
long long fac[N + 4], ifac[N + 4];
long long qpow(long long a, long long b) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b /= 2;
    }
    return res;
}
long long f[2005][2005];
long long C(int n, int m) {
    return fac[m] * ifac[n] % mod * ifac[m - n] % mod;
}
int main() {
    cin >> n >> k;
    if (k == 1) {
        cout << 1 << endl;
        return 0;
    }
    fac[0] = fac[1] = ifac[1] = ifac[0] = 1;
    for (int i = 1; i <= N; i++) {
        fac[i] = 1ll * fac[i - 1] * i % mod;
    }
    ifac[N] = qpow(fac[N], mod - 2) % mod;
    for (int i = N - 1; i >= 2; i--) {
        ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
    }
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            f[i][j] = f[i - 1][j];
            if (!j) {
                continue;
            }
            f[i][j] = (f[i][j] +
                       f[i][j - 1] * (n - j + 1) % mod *
                           C(k - 2, n - i + (n - j + 1) * (k - 1) - 1) % mod) %
                      mod;
        }
    }
    cout << f[n][n] % mod;
    return 0;
}