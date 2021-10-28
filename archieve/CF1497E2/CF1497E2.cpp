#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
const int K = 25;
int square_free(int x) {
    int res = 1;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            int cnt = 0;
            while (x % i == 0) {
                cnt++;
                x /= i;
            }
            if (cnt & 1) {
                res *= i;
            }
        }
    }
    res *= x;
    return res;
}
int vis[10000001];
int dp[N][K];
int a[N], lb[K][N];
int main() {
    int _;
    cin >> _;
    while (_--) {
        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            a[i] = square_free(a[i]);
        }
        for (int i = 0; i <= k; i++) {
            for (int i = 1; i <= n; i++) {
                vis[a[i]] = 0;
            }
            int cnt = 0;
            for (int l = 1, r = 1; r <= n; ++r) {
                vis[a[r]]++;
                cnt += (vis[a[r]] >= 2);
                if (cnt > i) {
                    while (cnt > i) {
                        cnt -= (vis[a[l]] >= 2);
                        vis[a[l]]--;
                        l++;
                    }
                }
                lb[i][r] = l;
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                dp[i][j] = 0x3f3f3f3f;
            }
        }
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                for (int l = 0; l <= j; l++) {
                    dp[i][j] = min(dp[i][j], dp[lb[l][i] - 1][j - l] + 1);
                }
            }
        }
        int ans = 0x3f3f3f3f;
        for (int i = 0; i <= k; i++) {
            ans = min(ans, dp[n][i]);
        }
        cout << ans << '\n';
    }
    return 0;
}
// Asusetic eru quionours.