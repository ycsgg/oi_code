### P5363 [SDOI2019]移动金币

容易发现如果把棋子间的空格当作是一堆石子，那这个就是阶梯Nim博弈

那么套用结论，我们要用$m$个棋子把$n$格子分割成$m+1$段，要求从右往左第奇数个空段个数异或和为$0$

考虑统计必败态然后用总数减去

暴力的想法是$dp_{i,j,k}$表示从右往左考虑到$i$的位置上，放到了$j$个棋子并且钦定最后一个格子放一个，当前异或和为$k$，暴力转移

优化的话，考虑异或的性质，二进制拆分一下，设$dp_{i,j}$为做完了二进制第$i$位，现在有$j$个格子未处理，那么
$$
dp_{i,j}=\sum\limits_{2|k}dp_{i+1,j-k\times2^i}\binom{\lfloor\frac{m+1}{2}\rfloor}{k}
$$

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 9;
const int N  = 152338;
ll n, m;
ll cnt;
ll fac[N], invfac[N];
ll dp[20][N];
ll c[233];
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
ll C(ll n, ll m) {
    if (m < 0 || m > n) {
        return 0;
    }
    return fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}
int main() {
    cin >> n >> m;
    n -= m;
    fac[0] = 1;
    for (int i = 1; i <= n + m; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    invfac[n + m] = qpow(fac[n + m], mod - 2);
    for (int i = n + m - 1; i >= 0; i--) {
        invfac[i] = invfac[i + 1] * (i + 1) % mod;
    }
    cnt    = C(n + m, m);
    int p2 = 1;
    while ((1 << p2) <= n) {
        p2++;
    }
    for (int i = 0; i <= (m + 1); i++) {
        c[i] = C((m + 1) / 2, i);
    }
    dp[p2][n] = 1;
    for (int i = p2 - 1; i >= 0; i--) {
        for (int j = 0; j <= n; j++) {
            if (!dp[i + 1][j])
                continue;
            for (int k = 0; k <= (m + 1) / 2 && k * (1 << i) <= j; k += 2) {
                dp[i][j - k * (1 << i)] =
                    ((dp[i + 1][j] * c[k] % mod) + dp[i][j - k * (1 << i)]) %
                    mod;
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i <= n; i++) {
        ans +=
            (dp[0][i] *
             C(i + (m + 1 - (m + 1) / 2) - 1, (m + 1 - (m + 1) / 2) - 1) % mod);
        ans %= mod;
    }
    cout << (1ll * cnt - ans + mod) % mod << endl;
    return 0;
}
```