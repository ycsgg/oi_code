#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e5 + 5, M = 1005;
int val[M][M], dp[M][M];
int q[N], mmax[M], dis[N];
int n, m;
int Y(int k) {
    return (dis[k] + k * k - dp[mmax[k]][k]);
}
int calc(int i, int j, int k) {
    return ((i - mmax[k]) * (i - mmax[k]) + (j - k) * (j - k));
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x, y, v;
        cin >> x >> y >> v;
        val[x][y] = v;
    }
    memset(dp, -0x3f, sizeof(dp));
    dp[1][1]  = val[1][1];
    val[1][1] = 0;
    mmax[1]   = 1;
    for (int i = 1; i <= m; i++) {
        int head = 0, tail = 0;
        q[0] = 0;
        for (int j = 1; j <= m; j++) {
            dis[j] = (mmax[j] != 0) ? (i - mmax[j]) * (i - mmax[j]) : 0;
        }
        for (int j = 1; j <= m; j++) {
            if (mmax[j]) {
                while (head < tail &&
                       (Y(q[tail]) - Y(q[tail - 1])) * (j - q[tail]) >=
                           (Y(j) - Y(q[tail])) * (q[tail] - q[tail - 1]))
                    tail--;
                q[++tail] = j;
            }
            if (!val[i][j])
                continue;
            while (head < tail && Y(q[head + 1]) - Y(q[head]) <=
                                      2 * j * (q[head + 1] - q[head])) {
                head++;
            }
            int k    = q[head];
            dp[i][j] = dp[mmax[k]][k] - calc(i, j, k) + val[i][j];
            mmax[j]  = i;
            dis[j]   = 0;
            while (head < tail &&
                   (Y(q[tail]) - Y(q[tail - 1])) * (j - q[tail]) >=
                       (Y(j) - Y(q[tail])) * (q[tail] - q[tail - 1])) {
                tail--;
            }
            q[++tail] = j;
        }
    }
    cout << dp[m][m];
    return 0;
}
// Asusetic eru quionours