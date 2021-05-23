#include <iostream>
using namespace std;
typedef long long ll;
const int N    = 2005;
const int Offset = N * 3;
ll mod;
int n;
ll dp[N * 3][N * 6];
int main() {
    cin >> n >> mod;
    dp[0][0 + Offset] = 1;
    for (int i = 0; i < n * 3; i++) {
        for (int j = -i; j <= i; j++) {
            dp[i + 1][j + 1 + Offset] += dp[i][j + Offset];
            dp[i + 1][j + 1 + Offset] %= mod;
            dp[i + 2][j - 1 + Offset] += dp[i][j + Offset] * (i + 1) % mod;
            dp[i + 2][j + 1 + Offset] %= mod;
            dp[i + 3][j + Offset] +=
                1ll * dp[i][j + Offset] * (i + 1) % mod * (i + 2) % mod;
            dp[i + 3][j + 1 + Offset] %= mod;
        }
    }
    ll ans = 0;
    for (int i = 0; i <= n * 3; i++) {
        ans += dp[n * 3][i + Offset];
        ans %= mod;
    }
    cout << ans;
    return 0;
}
// Asusetic eru quionours
