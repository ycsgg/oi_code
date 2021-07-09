#include <cstring>
#include <iostream>
using namespace std;
const int N = 105;
using ll    = long long;
char ch[N];
ll a[N], dp[N][N][N];
int main() {
    int len;
    cin >> len;
    cin >> (ch + 1);
    for (int i = 1; i <= len; i++) {
        cin >> a[i];
    }
    for (int i = len; i; i--) {
        for (int j = i; j <= len; j++) {
            for (int k = 0; k < len; k++) {
                dp[i][j][k] = dp[i][j - 1][0] + a[k + 1];
                for (int l = i; l < j; l++) {
                    if (ch[l] != ch[j])
                        continue;
                    dp[i][j][k] =
                        max(dp[i][j][k], dp[l + 1][j - 1][0] + dp[i][l][k + 1]);
                }
            }
        }
    }
    cout << dp[1][len][0] << endl;
}
// Asusetic eru quionours
