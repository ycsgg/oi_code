### AT1975 [ARC058C] Iroha and Haiku

思考一下发现直接统计方案很难保证不重

所以统计不合法的

数据范围就很状压，考虑 $x+y+z \le 17$ 所以得用 $2^{x+y+z}$ 个状态

考虑直接把数字放在对应的位置上，比如

 $4 \rightarrow 1000$ $3 \rightarrow 100$

那么符合条件的就是 $x+y+z-1$ $y+z-1$ $z-1$ 位都是 $1$ 

$dp$ 统计不合法的 $dp_{i,S}$ 就是前 $i$ 个数字状态是 $S$ 的方案，只要不合法就转移就可

```cpp
/*
さびしさや
一尺消えて
ゆくほたる
*/
#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b /= 2;
    }
    return res;
}
ll n, x, y, z;
ll S;
ll ans;
ll bitadd(ll x, ll i) {
    return ((x << i) | (1 << (i - 1))) & (S - 1);
}
ll mask;
bool check(ll state) {
    return ((state & mask) == mask);
}
int dp[42][(1 << 18)];
int main() {
    cin >> n >> x >> y >> z;
    ans  = qpow(10, n);
    mask = (1 << (x + y + z - 1));
    mask |= (1 << (y + z - 1));
    mask |= (1 << (z - 1));
    dp[0][0] = 1;
    S        = (1 << (x + y + z));
    for (int i = 1; i <= n; i++) {
        for (int s = 0; s < S; s++) {
            for (int k = 1; k <= 10; k++) {
                ll u = bitadd(s, k);
                if (!check(u)) {
                    dp[i][u] = (dp[i][u] + dp[i - 1][s]) % mod;
                }
            }
        }
    }
    for (int s = 0; s < S; s++) {
        ans = (ans - dp[n][s] + mod) % mod;
    }
    cout << ans << endl;
}
// Asusetic eru quionours
```

