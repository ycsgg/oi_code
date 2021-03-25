#include <algorithm>
#include <iostream>
using namespace std;
const int N = 5e4 + 5, M = 505;
int n, m;
int dp[N][M];
int k[N], p[N], tmp[2 * N], x[N];
int sum[N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> k[i] >> p[i];
        tmp[i] = k[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        tmp[i + n] = x[i];
    }
    sort(tmp + 1, tmp + 1 + n * 2);
    int cnt = unique(tmp + 1, tmp + 1 + n * 2) - tmp - 1;
    for (int i = 1; i <= n; i++) {
        k[i] = lower_bound(tmp + 1, tmp + 1 + cnt, k[i]) - tmp;
        x[i] = lower_bound(tmp + 1, tmp + 1 + cnt, x[i]) - tmp;
    }
    int mmax = -1;
    for (int i = 1; i <= n; i++) {
        mmax = max(mmax, p[i]);
        sum[k[i]] += p[i];
        for (int j = 0; j <= min(i, m); j++) {
            if (i != 1 && j != 0) {
                dp[i][j] =
                    max(dp[i][j], dp[i - 2][j - 1] + 2 * max(sum[x[i]], mmax));
            }
            dp[i][j] = max(dp[i][j], dp[i - 1][j] + max(sum[x[i]], mmax));
        }
    }
    int ans = 0;
    for (int i = 0; i <= m; i++) {
        ans = max(dp[n][i], ans);
    }
    cout << ans;
    return 0;
}
