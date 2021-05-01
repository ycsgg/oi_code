#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
ll n, m;
ll dp[(1 << 18) + 10][105][2];
int a[20], cnt;
bool vis[19];
int main() {
    cin >> n >> m;
    while (n) {
        a[cnt++] = n % 10;
        n /= 10;
    }
    dp[0][0][0] = 1;
    for (int s = 0; s < (1 << cnt); s++) {
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < cnt; i++) {
            if ((s & (1 << i)) || vis[a[i]])
                continue;
            vis[a[i]] = 1;
            for (int j = 0; j < m; j++) {
                if (a[i]) {
                    dp[s | (1 << i)][(j * 10 + a[i]) % m][1] += dp[s][j][0];
                    dp[s | (1 << i)][(j * 10 + a[i]) % m][1] += dp[s][j][1];
                } else {
                    dp[s | (1 << i)][(j * 10 + a[i]) % m][1] += dp[s][j][1];
                }
            }
        }
    }
    cout << dp[(1 << cnt) - 1][0][1];
    return 0;
}
// Asusetic eru quionours
