#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int mod = 1e9 + 7;
constexpr int N = 505;
char s[N];
ll dp[N][N][4];
int pre[N][N];
int n, K;
int main() {
    cin >> n >> K;
    cin >> (s + 1);
    for (int i = 1; i <= n; i++) {
        pre[i + 1][i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n && j - i + 1 <= K; j++) {
            if (s[j] == '*' || s[j] == '?') {
                pre[i][j] = 1;
            } else {
                break;
            }
        }
    }
    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            if ((s[l] == '(' || s[l] == '?') && (s[r] == ')' || s[r] == '?')) {
                dp[l][r][0] = (dp[l][r][0] + pre[l + 1][r - 1]) % mod;
                for (int k = 1; k <= 3; k++) {
                    dp[l][r][0] = (dp[l][r][0] + dp[l + 1][r - 1][k]) % mod;
                }
                // -----------
                for (int k = l + 1; k < r; k++) {
                    dp[l][r][3] =
                        (dp[l][r][3] + dp[l][k][0] * dp[k + 1][r][3] % mod) %
                        mod;
                    dp[l][r][3] =
                        (dp[l][r][3] + dp[l][k][0] * dp[k + 1][r][1] % mod) %
                        mod;
                }
            }
            // -----------
            dp[l][r][3] = (dp[l][r][3] + dp[l][r][0]) % mod;
            if (s[r] != '*') {
                int lim = min(r - l, K);
                for (int k = 1; k <= lim; k++) {
                    if (s[l + k - 1] == '*' || s[l + k - 1] == '?') {
                        dp[l][r][1] = (dp[l][r][1] + dp[l + k][r][3]) % mod;
                    } else {
                        break;
                    }
                }
            }
            if (s[l] != '*') {
                int lim = min(r - l, K);
                for (int k = 1; k <= lim; k++) {
                    if (s[r - k + 1] == '*' || s[r - k + 1] == '?') {
                        dp[l][r][2] = (dp[l][r][2] + dp[l][r - k][3]) % mod;
                    } else {
                        break;
                    }
                }
            }
        }
    }
    cout << dp[1][n][3];
    return 0;
}