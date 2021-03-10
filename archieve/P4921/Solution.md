### P4931 [MtOI2018]情侣？给我烧了！（加强版）

大力推柿子

记$f_k$是$k$对情侣都不匹配的方案数

计算$k$对匹配可以从男女中各选出$\binom{n}{k}$种，$k$对随便排，顺序可以互换，答案为$\binom{n}{k}^22^kk!f_{n-k}$

显然的
$\sum\binom{n}{k}^22^kk!f_{n-k}=(2n)!$，因为所有情况之和就是所有排列数

展开
$\sum\frac{k!2^k}{(k!)^2}\frac{f_{n-k}}{((n-k)!)^2}=\frac{(2n)!}{(n!)^2}$

左边的$\frac{k!2^k}{(k!)^2}=\frac{2^k}{k!}$的生成函数为$e^{2x}$，右边的$\frac{(2n)!}{(n!)^2}$生成函数为$\frac{1}{\sqrt{1-4x}}$（广义二项式

所以$e^{2x}F=\frac{1}{\sqrt{1-4x}}$

$F=\frac{e^{-2x}}{\sqrt{1-4x}}$

$F'=8x(1-4x)^{-\frac{3}{2}}e^{-2x}=\frac{8xF}{1-4x}$

$F'=4xF'+8xF$

考虑对生成函数微分的性质，那么$\frac{f_{n+1}}{n!(n+1)!}=\frac{f_n}{n!(n-1)!}+\frac{f_{n-1}}{((n-1)!)^2}$

整理一下可得到$f_n=4n(n-1)f_{n-1}+8n(n-1)^2f_{n-2}$

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const int N  = 5e6 + 500;
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
struct Query {
    ll n, k;
} q[300005];
ll T, n;
ll fac[N], invfac[N], f[N], inv[N];
int main() {
    cin >> T;
    fac[0] = fac[1] = invfac[0] = invfac[1] = inv[1] = 1;
    for (int i = 1; i <= T; i++) {
        cin >> q[i].n >> q[i].k;
        n = max(q[i].n, n);
    }
    f[0] = 1;
    f[1] = 0;
    for (int i = 2; i <= n; i++) {
        f[i] = 4ll * i * (1ll * i - 1ll) % mod * f[i - 1] % mod +
               8ll * i * (1ll * i - 1ll) % mod * (1ll * i - 1ll) % mod *
                   f[i - 2] % mod;
    }
    for (int i = 1; i <= n; i++) {
        fac[i] = 1ll * fac[i - 1] * i % mod;
    }
    invfac[n] = qpow(fac[n], mod - 2);
    for (int i = n - 1; i >= 2; i--) {
        invfac[i] = 1ll * invfac[i + 1] * 1ll * (i + 1) % mod;
    }
    for (int i = 1; i <= n; i++) {
        fac[i] = 1ll * fac[i] * fac[i] % mod;
    }
    for (int i = 1; i <= T; i++) {
        cout << 1ll * fac[q[i].n] % mod * invfac[q[i].k] % mod *
                    invfac[q[i].n - q[i].k] % mod * invfac[q[i].n - q[i].k] %
                    mod * qpow(2, q[i].k) % mod * f[q[i].n - q[i].k] % mod
             << endl;
    }
    return 0;
}
```