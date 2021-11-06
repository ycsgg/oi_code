#include <cstring>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
const int Lim = 567;
ll a[N], s[N], dp[N][Lim + 1];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int _;
    cin >> _;
    while (_--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            s[i] = s[i - 1] + a[i];
        }
        for (int i = 1; i <= n + 5; i++) {
            for (int j = 1; j < Lim; j++) {
                dp[i][j] = 0;
            }
        }
        for (int i = n; i; i--) {
            for (int j = 1; j < Lim && i + j - 1 <= n; j++) {
                dp[i][j] = dp[i + 1][j];
                if (j == 1) {
                    dp[i][j] = max(dp[i][j], a[i]);
                } else {
                    if (s[i + j - 1] - s[i - 1] < dp[i + j][j - 1]) {
                        dp[i][j] = max(dp[i][j], s[i + j - 1] - s[i - 1]);
                    }
                }
            }
        }
        for (int i = Lim - 1; i; i--) {
            if (dp[1][i]) {
                cout << i << '\n';
                break;
            }
        }
    }
}
// Asusetic eru quionours.