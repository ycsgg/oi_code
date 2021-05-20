### CF1430F Realistic Gameplay

发现如果 $r_i < l_{i+1}$ 那么就直接枚举即可，因为中间最多换一次子弹

但是这个题可以交于上一次的终点，所以考虑倒着递推，考虑每波开始前最少有多少子弹

如果这一个与下一波不相交那么

$dp_i=a_i-k(r_i-l_i)$

因为除了第一秒都可以换一次子弹

第一秒是 $dp_i$

相交的话要在最后一秒留下 $dp_{i+1}$ 个子弹

即 $dp_i=a_i+dp_{i+1}-k(r_i-l_i)$

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
int n;
int k;
ll l[2003], r[2003], a[2003];
ll dp[2003];
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> l[i] >> r[i] >> a[i];
    }
    for (int i = n; i >= 1; --i) {
        ll rq = a[i];
        if (i != n) {
            rq += (r[i] == l[i + 1] ? dp[i + 1] : 0);
        }
        if ((r[i] - l[i] + 1) * k < rq) {
            cout << -1 << endl;
            exit(0);
        }
        dp[i] = max(rq - (r[i] - l[i]) * k, 0ll);
    }
    ll ans = 0, cur = k;
    for (int i = 1; i <= n; ++i) {
        if (cur < dp[i]) {
            ans += cur;
            cur = k;
        }
        ans += a[i];
        cur = ((cur - a[i]) % k + k) % k;
    }
    cout << ans;
    return 0;
}
// Asusetic eru quionours.
```

