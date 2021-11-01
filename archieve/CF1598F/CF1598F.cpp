#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int OFFSET = 400005;
int n;
string s[22];
int sum[22], mmin[22];
int g[22][OFFSET * 2];
int tot[(1 << 20) + 1], dp[(1 << 20) + 1][2];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        mmin[i] = 0x3f3f3f3f;
        for (auto c : s[i]) {
            sum[i] += (c == '(' ? 1 : -1);
            mmin[i] = min(mmin[i], sum[i]);
            if (sum[i] == mmin[i]) {
                g[i][OFFSET + sum[i]]++;
            }
        }
        tot[1 << i] = sum[i];
    }
    for (int S = 1; S < (1 << n); S++) {
        int p = S & (-S);
        if (S == p) {
            continue;
        }
        tot[S] = tot[S - p] + tot[p];
    }
    for (int S = 1; S < (1 << n); S++) {
        dp[S][0] = dp[S][1] = -0x3f3f3f3f;
    }
    int ans = 0;
    for (int S = 0; S < (1 << n); S++) {
        for (int i = 0; i < n; i++) {
            if (S & (1 << i)) {
                continue;
            }
            int T = S | (1 << i);
            if (tot[S] + mmin[i] >= 0) {
                dp[T][1] = max(dp[T][1], dp[S][1] + g[i][OFFSET - tot[S]]);
                // printf("[%d,%d] -> [%d,%d] : [%d,%d]\n", S, 1, T, 1, i,
                //        -tot[S]);
            } else {
                dp[T][0] = max(dp[T][0], dp[S][1] + g[i][OFFSET - tot[S]]);
                // printf("[%d,%d] -> [%d,%d] : [%d,%d]\n", S, 1, T, 1, i,
                //        -tot[S]);
            }
        }
    }
    for (int S = 0; S < (1 << n); S++) {
        ans = max(ans, max(dp[S][0], dp[S][1]));
    }
    cout << ans;

    return 0;
}
// Asusetic eru quionours.