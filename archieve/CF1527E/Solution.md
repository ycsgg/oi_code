### CF1527E Partition Game

决策单调性优化DP

考虑朴素dp $dp_{i,j}=\min{dp_{k,j-1}+w(k+1,i)}$

这个看起来很满足四边形不等式可以决策单调性

不过暴力计算 $w$ 的话是 $O(n)$ 的，总复杂度 $O(kn^2\log n)$

这种每次只会单调移动一个端点用类似莫队的方式处理，均摊 $O(1)$

总复杂度 $O(kn\log n)$

```cpp
#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N   = 35005;
const int INF = 0x3f3f3f3f;
int n, k;
array<int, N> a, pre, last, nxt;
array<array<int, 2>, N> dp;
int now;
int pl = 1, pr = 0, sum = 0;
int calc(int l, int r) {
    while (pl < l) {
        if (nxt[pl] <= pr) {
            sum -= nxt[pl] - pl;
        }
        ++pl;
    }
    while (pl > l) {
        --pl;
        if (nxt[pl] <= pr) {
            sum += nxt[pl] - pl;
        }
    }
    while (pr < r) {
        ++pr;
        if (pre[pr] >= pl) {
            sum += pr - pre[pr];
        }
    }
    while (pr > r) {
        if (pre[pr] >= pl) {
            sum -= pr - pre[pr];
        }
        --pr;
    }
    return sum;
}
void solve(int l, int r, int x, int y) {
    if (l > r || x > y) {
        return;
    }
    int mid = (l + r) / 2;
    int val = INF, pos;
    for (int i = x; i < mid && i <= y; i++) {
        int tmp = dp[i][now ^ 1] + calc(i + 1, mid);
        if (tmp < val) {
            pos = i;
            val = tmp;
        }
    }
    dp[mid][now] = val;
    solve(l, mid - 1, x, pos);
    solve(mid + 1, r, pos, y);
}
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i]     = last[a[i]];
        last[a[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        last[a[i]] = n + 1;
    }
    for (int i = n; ~i; i--) {
        nxt[i]     = last[a[i]];
        last[a[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        dp[i][now] = INF;
    }
    while (k--) {
        now ^= 1;
        solve(1, n, 0, n);
    }
    cout << dp[n][now] << endl;
    return 0;
}
// Asusetic eru quionours
```

#DP

#决策单调性