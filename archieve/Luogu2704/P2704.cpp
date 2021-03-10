
#include <iostream>
using namespace std;
const int MAXN = (1 << 10) + 5;
int n, m;
int a[105];
int dp[MAXN][MAXN][3];
int sum[MAXN];
int getsum(int x) {
    int tot = 0;
    while (x) {
        tot += (x & 1);
        x = x >> 1;
    }
    return tot;
}
bool check(int x) {
    return (x & (x << 1)) || (x & (x << 2));
}
int ans = -1;
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char tmp;
            cin >> tmp;
            a[i] = a[i] << 1;
            a[i] += (tmp == 'H');
        }
    }
    for (int i = 0; i < (1 << m); i++) {
        sum[i] = getsum(i);
        if (!((i & a[0]) || check(i))) {
            dp[0][i][0] = sum[i];
        }
    }
    for (int i = 0; i < (1 << m); i++) {
        for (int j = 0; j < (1 << m); j++) {
            if (!((i & j) || (i & a[0]) || (j & a[1]) || check(i) ||
                  check(j))) {
                dp[i][j][1] = sum[i] + sum[j];
            }
        }
    }
    for (int i = 2; i < n; i++) {
        for (int s = 0; s < (1 << m); s++) {
            if ((s & a[i - 1]) || check(s)) {
                continue;
            }
            for (int l = 0; l < (1 << m); l++) {
                if ((l & a[i]) || check(l) || (l & s)) {
                    continue;
                }
                for (int now = 0; now < (1 << m); now++) {
                    if((now&s)||(now&l)||check(now)||(now&a[i-2])){
                        continue;
                    }
                    dp[s][l][i % 3] = max(dp[s][l][i % 3], dp[now][s][(i-1)%3]+sum[l]);
                }
            }
        }
    }
    for (int s = 0; s < (1 << m);s++){
        for (int l = 0; l < (1 << m);l++){
            ans = max(ans, dp[s][l][(n - 1) % 3]);
        }
    }
    cout << ans << endl;
}


