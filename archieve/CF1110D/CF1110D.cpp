#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int n, m;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    vector<int> cnt(m + 1);
    vector<array<array<int, 3>, 3>> dp(m + 1, array<array<int, 3>, 3>());
    for (auto q : dp) {
        for (auto k : q) {
            k.fill(-1);
        }
    }
    dp[0][0][0] = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    if (cnt[i] < j + k + l)
                        continue;
                    // printf("%d %d %d %d\n", i, j, k, l);
                    dp[i][k][l] =
                        max(dp[i][k][l],
                            dp[i - 1][j][k] + (cnt[i] - j - k - l) / 3 + l);
                }
            }
        }
    }
    cout << dp[m][0][0];
    return 0;
}
// Asusetic eru quionours.