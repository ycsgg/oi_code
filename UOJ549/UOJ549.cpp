#include <cstring>
#include <iostream>
const int N = 6e4 + 10;
using namespace std;
const int inf = 1e9 + 10;
const int Base = 8, Mask = (1 << Base) - 1;
int n, k;
int a[N], dp[N], kx[N], mmin[300][300];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i] ^= a[i - 1];
    }
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = inf;
    }
    for (int i = 1; i <= k; ++i) {
        for (int x = 0; x <= Mask; ++x) {
            for (int y = 0; y <= Mask; ++y) {
                mmin[x][y] = inf;
            }
        }
        for (int j = 0; j <= n; ++j) {
            kx[j] = inf;
            for (int x = 0; x <= Mask; ++x) {
                kx[j] = min(kx[j],
                            mmin[x][a[j] & Mask] + ((a[j] >> Base ^ x) << 8));
            }
            for (int x = 0; x <= Mask; ++x) {
                mmin[a[j] >> Base][x] =
                    min(mmin[a[j] >> Base][x], dp[j] + ((a[j] & Mask) ^ x));
            }
        }
        for (int j = 0; j <= n; ++j) {
            dp[j] = kx[j];
        }
    }
    for (int i = k; i <= n; ++i) {
        cout << dp[i] << ' ';
    }
    return 0;
}