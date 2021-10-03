#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
const int N = 2005;
int k;
ll pa, pb;
ll A, B;
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
    cin >> k >> pa >> pb;
    A = pa * qpow((pa + pb) % mod, mod - 2) % mod;
    B = (1 - A + mod) % mod;
    auto ADivB = A * qpow(B, mod - 2) % mod;
    for (int i = k; i >= 1; i--) {
        for (int j = k; j >= 0; j--) {
            if (i + j >= k) {
                dp[i][j] = ((i + j) % mod + ADivB) % mod;
            } else {
                dp[i][j] =
                    (dp[i + 1][j] * A % mod + dp[i][i + j] * B % mod) % mod;
            }
        }
    }
    cout << dp[1][0];
    return 0;
}
// Asusetic eru quionours.