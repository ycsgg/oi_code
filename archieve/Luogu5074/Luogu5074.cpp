#include <array>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        int mp[13][13];
        vector<ll> dp[2];
        dp[0].resize(1 << m + 1);
        dp[1].resize(1 << m + 1);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> mp[i][j];
            }
        }
        auto getpos = [](int x, int pos) -> int {
            return x & (1 << pos - 1);
        };
        auto change = [](int &x, int pos, bool v) -> void {
            x &= ~(1 << pos - 1);
            x |= (v << pos - 1);
        };
        int cur = 0;
        dp[1][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                for (int S = 0; S < (1 << m + 1); S++) {
                    int now = S;
                    int left = getpos(S, j);
                    int up = getpos(S, j + 1);
                    if (!mp[i][j]) {
                        if (!left && !up) {
                            dp[cur][S] += dp[cur ^ 1][S];
                        }
                        continue;
                    }
                    if (!left && !up) {
                        change(now, j, 1);
                        change(now, j + 1, 1);
                        dp[cur][now] += dp[cur ^ 1][S];
                    } else if (left && up) {
                        change(now, j, 0);
                        change(now, j + 1, 0);
                        dp[cur][now] += dp[cur ^ 1][S];
                    } else {
                        change(now, j, 1);
                        change(now, j + 1, 0);
                        dp[cur][now] += dp[cur ^ 1][S];
                        change(now, j, 0);
                        change(now, j + 1, 1);
                        dp[cur][now] += dp[cur ^ 1][S];
                    }
                }
                dp[cur ^ 1].assign(1 << m + 1, 0);
                cur ^= 1;
            }
            for (int j = (1 << m) - 1; ~j; j--) {
                dp[cur][j << 1] = dp[cur ^ 1][j];
            }
            dp[cur ^ 1].assign(1 << m + 1, 0);
            cur ^= 1;
        }
        cout << dp[cur ^ 1][0] << endl;
    }
    return 0;
}
// Asusetic eru quionours