### P7519 [省选联考 2021 A/B 卷] 滚榜

部分分可以暴力枚举全排列

对一个排列 $\pi$ ，贪心的分配使得 $b_i$ 尽可能小即可

具体来说若 $\pi_i>\pi_{i-1}$ 那因为 $b_i$ 不降就取 $b_{i-1}$ 否则取 $b_i=b_{i-1}+\pi_{i-1}-\pi_i$ （还需要考虑下分数相同标号小的放前面）

然后枚举全排列 $O(n!)$ 即可拿到 60pts 的好成绩3$）

dp 是 $f[S][i][j]$ 表示状态为 $S$ 上一个人是 $i$ 当前用掉的 $\sum b_i$ (并没炸空间，我失了智了)

可以发现 $\sum b_i=\sum\max(\pi_{i-1}-\pi_i,0)(n-i+1)$

枚举状态时枚举下一个人

```cpp
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
```

