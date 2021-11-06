#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 2005;
ll dp[N][N];
ll l[N], r[N];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
    }
    int lim = n / 2;
    if (n & 1) {
        dp[1][0] = 1ll * lim * (lim + 1) * (r[2] - l[2]);
    } else {
        dp[0][0] = 1ll * lim * lim * (r[1] - l[1]);
    }
    for (int i = (n & 1); i < n; i++) {
        for (int j = max(0, i - (n & 1) - lim); j <= min(i - (n & 1), lim);
             j++) {
            int cntl = lim - j;
            int cntr = lim - i + j + (n & 1);
            auto lenl = l[i + 1] - l[i + 2];
            auto lenr = r[i + 2] - r[i + 1];
            dp[i + 1][j] =
                max(dp[i + 1][j], dp[i][j] + 1ll * cntl * (n - cntl) * lenl +
                                      1ll * (cntr - 1) * (n - cntr + 1) * lenr);
            dp[i + 1][j + 1] =
                max(dp[i + 1][j + 1],
                    dp[i][j] + 1ll * (cntl - 1) * (n - cntl + 1) * lenl +
                        1ll * cntr * (n - cntr) * lenr);
        }
    }
    cout << dp[n][lim] + 1ll * n * (n - 1) * (n + 1) / 6;
    return 0;
}
// Asusetic eru quionours.
