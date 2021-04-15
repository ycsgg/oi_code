#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 13, M = 500;
int n, m, S, a[N + 1], id[1 << N | 1];
long long dp[(1 << N) + 1][N + 1][M + 1];
int lowbit(int x) {
    return x & (-x);
}
int mmax = -1, maxid;
int main() {
    cin >> n >> m;
    S = (1 << n) - 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] > mmax) {
            mmax  = a[i];
            maxid = i;
        }
        id[1 << (i - 1)] = i;
    }
    for (int i = 1; i <= n; i++) {
        int v = n * (mmax - a[i] + (maxid < i));
        if (v <= m) {
            dp[1 << (i - 1)][i][v] = 1;
        }
    }
    for (int i = 1; i < S; i++) {
        int cnt = __builtin_popcount(i);
        for (int t = i; t; t -= lowbit(t)) {
            for (int sum = 0; sum <= m; sum++) {
                int pos = id[lowbit(t)];
                for (int j = 1; j <= n; ++j) {
                    if ((i & (1 << (j - 1)))) {
                        continue;
                    } else {
                        int v =
                            sum + (n - cnt) * max(0, (pos < j) + a[pos] - a[j]);
                        if (v <= m) {
                            dp[i | (1 << (j - 1))][j][v] += dp[i][pos][sum];
                        }
                    }
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            ans += dp[S][j][i];
        }
    }
    cout << ans;
    return 0;
}