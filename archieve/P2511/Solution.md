### P2511 [HAOI2008]木棍分割

二分长度，统计方案的话就是dp

dp设$dp_{i,j}$表示前$j$个木棍，分成$i$组的方案数

$dp[i][j]=\sum\limits_{l=k}^{j-1}dp[i-1][l] \quad k=min\{sum[j]-sum[k]>=len\}$

$ans=\sum dp[i][n]$

可以发现$sum$单调不减，所以只要一个$k$满足条件，后面的一定满足，记$S[i][j]=\sum_{k=0}^jdp[i][k]$

那么$dp[i][j]=S[i-1][j]-S[i-1][k-1] \quad k=min\{sum[j]-sum[k]>=len\}$

然后$k$相对于某个点是固定的，可以预处理

然后还能滚掉一维

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int N   = 5e4 + 6;
const int mod = 10007;
int a[N], s[N];
int sum[N], dp[N];
int pos[N];
int n, m;
int mmax = -1;
bool check(int len) {
    int tot = 0, now = 0;
    for (int i = 1; i <= n; i++) {
        if (now + a[i] > len) {
            tot++;
            now = a[i];
        } else {
            now += a[i];
        }
        if (tot > m) {
            return 0;
        }
    }
    return tot <= m;
}
int Count(int len) {
    int k = 0;
    for (int i = 1; i <= n; i++) {
        for (; k < i; k++) {
            if (s[i] - s[k] <= len) {
                pos[i] = k;
                break;
            }
        }
    }
    int res = (s[n] <= len);
    for (int i = 1; i <= n; i++) {
        if (s[i] <= len) {
            dp[i] = 1;
        }
        sum[i] = (sum[i - 1] + dp[i]) % mod;
    }
    for (int i = 2; i <= m + 1; i++) {
        for (int j = 1; j <= n; j++) {
            dp[j] = sum[j - 1];
            if (pos[j]) {
                dp[j] = (dp[j] - sum[pos[j] - 1] + mod) % mod;
            }
        }
        for (int j = 1; j <= n; j++) {
            sum[j] = (sum[j - 1] + dp[j]) % mod;
        }
        res = (res + dp[n]) % mod;
    }
    return res;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        s[i] = s[i - 1] + a[i];
        mmax = max(mmax, a[i]);
    }
    int l = mmax, r = s[n], ans;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            r   = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << " ";
    cout << Count(ans);
    return 0;
}
```