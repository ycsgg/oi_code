#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 998244353;
const int N = 22;
int n;
ll a[N], sum[(1 << N) + 5];
ll g[(1 << N) + 5], f[(1 << N) + 5][2];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int S = 0; S < (1 << n); S++) {
        for (int i = 1; i <= n; i++) {
            if (S & (1 << i - 1)) {
                sum[S] = sum[S] + a[i];
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] < 0) {
            f[1 << (i - 1)][0] = 1;
        } else {
            f[1 << (i - 1)][1] = 1;
        }
    }
    for (int S = 1; S < (1 << n); S++) {
        for (int i = 1; i <= n; i++) {
            if (S & (1 << i - 1))
                continue;
            auto T = S | (1 << i - 1);
            f[T][sum[T] >= 0] = (f[T][sum[T] >= 0] + f[S][1]) % mod;
        }
    }
    g[0] = 1;
    for (int S = 0; S < (1 << n); S++) {
        if (!g[S])
            continue;
        for (int i = 1; i <= n; i++) {
            if (S & (1 << i - 1))
                continue;
            auto T = S | (1 << i - 1);
            if (sum[T] < 0) {
                g[T] = (g[T] + g[S]) % mod;
            }
        }
    }
    ll ans = 0;
    auto U = (1 << n) - 1;
    for (int S = 1; S < (1 << n); S++) {
        ans = (ans +
               (sum[S] % mod * (f[S][0] + f[S][1]) % mod * g[U - S]) % mod) %
              mod;
        ans %= mod;
    }
    cout << (ans + mod) % mod << endl;
    return 0;
}
// Asusetic eru quionours