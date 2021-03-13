### AT3981 [ARC093D] Dark Horse

考虑$1$放哪都成，不如钦定在一号点，最后答案乘$2^n$即可

剩下的需要保证区间$[2^{k-1}+1,2^k]$内的最小数字都不是$A_i$中的数字

都不是是个很麻烦的限制，考虑反演设$f_i$是恰好有$i$个区间$A$中的元素是最小值，$g_i$是至少有$i$个区间是

易见$g_i=\sum\limits_{j=i}^n\binom{j}{i}f_j \Leftrightarrow f_i=\sum\limits_{j=i}^n(-1)^{j-i}\binom{i}{j}g_i$

$g_i$可以状压 dp，具体来说，设$dp_{i,j}$表示现在考虑到$A_i$并且区间的状态为$j$的情况，其中$j$每一位二进制的$1$代表第$k$个区间填完了

因为要把一个$A_i$放在某一个区间中并且保证他最小，需要加入$2^k-1$个比他大的元素，从大到小排序，以防填数的时候把大的$A_i$填进去了

如果当前的$A_i$不作为最小值，那么$dp_{i,j}=dp_{i,j}+dp_{i-1,j}$

否则作为区间$k$的最小值，那么$dp_{i,j|2^k}=dp_{i,j|2^k}+dp_{i-1,j}\times \binom{2^k-1}{2^n-j-A_i}$

```cpp
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
const int LIM = 21;
const ll mod  = 1e9 + 7;
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
int n, m;
ll a[LIM];
ll pow2[LIM];
ll g[LIM][(1 << LIM) + 5];
ll fac[(1 << LIM) + 5], ifac[(1 << LIM) + 5];
ll C(int n, int m) {
    if (n < m)
        return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + 1 + m);
    reverse(a + 1, a + 1 + m);
    pow2[0] = 1;
    for (int i = 1; i < LIM; i++) {
        pow2[i] = pow2[i - 1] << 1ll;
    }
    fac[0] = 1;
    for (int i = 1; i <= pow2[LIM - 1]; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    ifac[pow2[LIM - 1]] = qpow(fac[pow2[LIM - 1]], mod - 2);
    for (int i = pow2[LIM - 1] - 1; i >= 0; i--) {
        ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
    }
    g[0][0] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < pow2[n]; j++) {
            g[i][j] = (g[i][j] + g[i - 1][j]) % mod;
            for (int k = 0; k < n; k++) {
                if (j & pow2[k])
                    continue;
                g[i][(j | pow2[k])] =
                    (g[i][(j | pow2[k])] +
                     g[i - 1][j] * C(pow2[n] - j - a[i], pow2[k] - 1) % mod *
                         fac[pow2[k]] % mod) %
                    mod;
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < pow2[n]; i++) {
        int res = __builtin_popcount(i);
        if (res & 1) {
            ans = (ans - g[m][i] * fac[pow2[n] - 1 - i] + mod) % mod;
        } else {
            ans = (ans + g[m][i] * fac[pow2[n] - 1 - i]) % mod;
        }
    }
    cout << ans * pow2[n] % mod;
    return 0;
}
```