#include <cstring>
#include <iostream>
using namespace std;
const int N = 25, D = 105, E = 105;
int n, e, d;
int t[E][D], dp[N][D];
int main() {
    cin >> n >> e >> d;
    memset(t, 0x3f, sizeof(t));
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i <= e; i++) {
        t[i][0] = 0;
    }
    for (int i = 1; i <= e; i++) {
        for (int j = 1; j <= d; j++) {
            for (int k = 1; k <= j & k * k <= i; k++) {
                t[i][j] = min(t[i][j], t[i - k * k][j - k] + 1);
            }
        }
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= d; j++) {
            int p = d - j;
            for (int k = 0; k <= j; k++) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - k] + t[e - p][k]);
            }
        }
    }
    cout << dp[n][d];
    return 0;
}