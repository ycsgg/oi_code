#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 998244353;
const int N = 505;
int n, x;
ll C[N][N];
ll dp[N][N];
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
int main() {
    cin >> n >> x;
    C[1][1] = 1;
    for (int i = 2; i <= n + 1; i++) {
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
        }
    }
    for (int i = 1; i <= x; i++) {
        dp[2][i] = i;
    }
    for (int i = 3; i <= n; i++) {
        for (int j = 1; j <= x; j++) {
            if (j < i) {
                dp[i][j] = qpow(j, i);
            } else {
                for (int k = 0; k <= i - 2; k++) {
                    dp[i][j] =
                        (dp[i][j] + C[i + 1][k + 1] * qpow(i - 1, k) % mod *
                                        dp[i - k][j - i + 1] % mod) %
                        mod;
                }
                dp[i][j] = (dp[i][j] + dp[i][i - 1]) % mod;
            }
        }
    }
    cout << dp[n][x];
    return 0;
}
// Asusetic eru quionours.