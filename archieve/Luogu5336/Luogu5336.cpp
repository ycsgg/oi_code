#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
using ll    = long long;
const int N = 55;
int n;
ll A, B;
ll dp[N][N][N][N];
ll nya[N][N];
ll a[N];
ll b[N];
int main() {
    cin >> n >> A >> B;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
    memset(dp, 0x3f, sizeof(dp));
    memset(nya, 0x3f, sizeof(nya));
    sort(b + 1, b + 1 + n);
    int tot = unique(b + 1, b + 1 + n) - b - 1;
    for (int i = 1; i <= n; i++) {
        a[i]                 = lower_bound(b + 1, b + 1 + tot, a[i]) - b;
        dp[i][i][a[i]][a[i]] = 0;
        nya[i][i]            = A;
    }
    for (int len = 1; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            for (ll x = 1; x <= tot; x++) {
                for (ll y = x; y <= tot; y++) {
                    auto &val = dp[l][r][min(x, a[r])][max(y, a[r])];
                    val       = min(val, dp[l][r - 1][x][y]);
                    for (int k = l; k < r; k++) {
                        dp[l][r][x][y] =
                            min(dp[l][r][x][y], dp[l][k][x][y] + nya[k + 1][r]);
                    }
                }
            }
            for (int x = 1; x <= tot; x++) {
                for (int y = x; y <= tot; y++) {
                    nya[l][r] =
                        min(nya[l][r], dp[l][r][x][y] + A +
                                           B * (b[y] - b[x]) * (b[y] - b[x]));
                }
            }
        }
    }
    cout << nya[1][n] << endl;
}
// Asusetic eru quionours.
// Asusetic eru quionours
