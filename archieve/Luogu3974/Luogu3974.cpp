#include <iostream>
using namespace std;
int t;
int a[1005][1005], dp[1005][1005];
int n, m;
int main() {
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> a[i][j];
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = m; j >= 1; j--) {
                dp[i][j] = max(dp[i - 1][j + 1] + a[i][j],
                               max(dp[i - 1][j], dp[i][j + 1]));
            }
        }
        cout << dp[n][1] << endl;
    }
    return 0;
}
// Asusetic eru quionours