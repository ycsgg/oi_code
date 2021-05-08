### CF868F Yet Another Minimization Problem

$O(n^2k)$ 的暴力 DP：$dp_{i,j}=\min\{dp_{k,j-1}+cnt(k+1,i)\}$ $dp_{i,j}$ 表示前 $i$ 个数分 $j$ 段

口胡一下可以发现这个是具有决策单调性的

具体来说因为 $j$ 始终不变，先省略掉，如果 $i \rightarrow i+1$ 那么 $cnt(k+1,i) \rightarrow cnt(k+1,i)+\sum\limits_{l=k+1}^i[a_l=a_{i+1}]$

考虑如果是 $dp_{k,j-1} \rightarrow dp_{i,j}$

那么对于 $dp_{i+1,j}$ 来说所有的 $p \le k$ 都有 $dp_{p,j-1} + cnt(p+1,i) \le dp_{k,j-1}+cnt(k+1,i)$

而当 $i$ 右移之后$dp_{p,j-1}$ 不变，$cnt(p+1,i+1)$ 变化量不小于 $cnt(k+1,i+1)$

所以最优决策必然单调

这样的话我们可以对 $[l,r]$ 分治，$[l,mid-1]$ 的决策点必然在 $[dp_{l,j-1},dp_{mid,j-1}]$ 中且不会在 $dp_{mid,j}$ 的决策点的右边，右边同理

$dp_{mid,j}$ 暴力转移

$cnt(l,r)$ 可以借助类似莫队的方法搞，因为每次拓展仅一次，所以均摊 $O(1)$

复杂度 $O(nk\log n)$

```cpp
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
int n, k;
ll a[N];
ll dp[N][2];
int now;
int ql = 1, qr;
ll res, _cnt[N];
void add(int x) {
    res += _cnt[x];
    ++_cnt[x];
}
void del(int x) {
    --_cnt[x];
    res -= _cnt[x];
}
ll cnt(int l, int r) {
    while (ql > l) {
        add(a[--ql]);
    }
    while (ql < l) {
        del(a[ql++]);
    }
    while (qr > r) {
        del(a[qr--]);
    }
    while (qr < r) {
        add(a[++qr]);
    }
    return res;
}
void solve(int l, int r, int L, int R) {
    if (l > r)
        return;
    int mid = (l + r) / 2;
    int cur = L;
    for (int i = min(mid, R); i >= L; i--) {
        ll tmp = dp[i - 1][now ^ 1] + cnt(i, mid);
        if (dp[mid][now] >= tmp) {
            dp[mid][now] = tmp;
            cur          = i;
        }
    }
    solve(l, mid - 1, L, cur);
    solve(mid + 1, r, cur, R);
}
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    memset(dp, 0x7f, sizeof(dp));
    dp[0][0] = 0;
    now      = 1;
    while (k--) {
        solve(1, n, 1, n);
        now ^= 1;
    }
    cout << dp[n][now ^ 1];
    return 0;
}
// Asusetic eru quionours
```

