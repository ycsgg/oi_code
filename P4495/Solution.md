### P4495 [HAOI2018]奇怪的背包

一个比较基础的结论是$v$在模$p$意义下能表示的数是$gcd(v,p)\times k$，多个数就是$gcd(v_1,v_2,v_3,\dots)\times k$

也是就每个$v$等价于$gcd(v,p)$

那么我们先搞出来$p$的约数，然后记录每个约数出现的个数$x_i$，因为不同仅有种类的不同，故这个约数给出的贡献是$2^{x_i}-1$

考虑dp，设$f_{i,j}$表示选取前$i$个约数当前$gcd$为$j$的答案

$\large f_{i,j}=f_{i-1,j}+(1+\sum\limits_{\mathrm{gcd}(v_k,v_i)=v_j}f_{i-1,k})\times(2^{x_i}-1)$

预处理$f$数组复杂度为$$O(d^2\log d)$$，$d$为约数个数，这个其实是很小的

对于询问$w_i$，答案是$\large\sum\limits_{v_j|w_i}f_{n,j}$，$O(qd)$，会T

不过实际上$w_i$变成$gcd(w_i,p)$是一样的

那么我们可以预处理所有的$\large ans_i=\sum\limits_{v_j|v_i}f_{n,j}$

```cpp
#include <algorithm>
#include <iostream>
using namespace std;
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
const int N   = 1e6 + 5;
const int mod = 1e9 + 7;
int n, p, q;
int v[N], cnt[N], d[N];
int tot[N];
int dp[2][N], ans[N];
int main() {
    cin >> n >> q >> p;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        v[i] = gcd(v[i], p);
    }
    cnt[1] = 2;
    for (int i = 2; i <= n; i++) {
        cnt[i] = 2ll * cnt[i - 1] % mod;
    }
    for (int i = 1; i <= n; i++) {
        cnt[i] = (cnt[i] - 1ll + mod) % mod;
    }
    int pcnt = 0;
    for (int i = 1; i * i <= p; i++) {
        if (p % i == 0) {
            d[++pcnt] = i;
        }
    }
    for (int i = pcnt; i > 1; i--) {
        if (p / d[i] != d[i]) {
            d[++pcnt] = p / d[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        int pos = lower_bound(d + 1, d + 1 + pcnt, v[i]) - d;
        tot[pos]++;
    }
    int now = 0;
    for (int i = 1; i <= pcnt; i++) {
        if (tot[i]) {
            now ^= 1;
            for (int j = 1; j <= pcnt; j++) {
                dp[now][j] = dp[now ^ 1][j];
            }
            for (int j = 1; j <= pcnt; j++) {
                if (dp[now ^ 1][j]) {
                    int k        = gcd(d[j], d[i]);
                    int pos      = lower_bound(d + 1, d + 1 + pcnt, k) - d;
                    dp[now][pos] = (dp[now][pos] +
                                    1ll * dp[now ^ 1][j] * cnt[tot[i]] % mod) %
                                   mod;
                }
            }
            dp[now][i] = (dp[now][i] + cnt[tot[i]] % mod) % mod;
        }
    }
    for (int i = 1; i <= pcnt; i++) {
        for (int j = 1; j <= i; j++) {
            if (d[i] % d[j] == 0) {
                ans[i] = (ans[i] + dp[now][j]) % mod;
            }
        }
    }
    while (q--) {
        int x;
        cin >> x;
        x       = gcd(x, p);
        int pos = lower_bound(d + 1, d + 1 + pcnt, x) - d;
        cout << ans[pos] << endl;
    }
    return 0;
}
```