### CF1264D Beautiful Bracket Sequence

大力推柿子

因为是一个子序列，所以我们考虑对于一个确定的括号序列，一定存在有一个划分点使得左边的左括号等于右边的右括号且等于其深度

证明显然

那么我们考虑每个划分点的贡献

对于每个划分点前面有 $l$ 个左括号，$?_l$ 个问号，后面有 $r$ 个右括号和 $?_r$ 个问号

那么我们枚举左边的括号，答案是

$\sum\limits_{i}(l+i)\binom{?_l}{i}\binom{?_r}{l+i-r}$

也就是左边选出来 $i$ 个问号变成 $($ ，右边相应的选 $l+i-r$ 个 $?$ 变成 $)$，然后乘上深度

推柿子

$l\sum\binom{?_l}{i}\binom{?_r}{l+i-r}=l\sum\binom{?_l}{i}\binom{?_r}{?_r-l-i+r}=l\binom{?}{?_r+r-l}$

另一边

$\sum i\binom{?_l}{i}\binom{?_r}{?_r-l-i+r}=\sum?_l\binom{?_l-1}{i-1}\binom{?_r}{?_r-l-i+r}=?_l\binom{?-1}{?_r+r-l-1}$

组合式子的基本技巧

然后求出来即可

```cpp
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int N  = 1e6 + 5;
const ll mod = 998244353;
char s[N];
int n;
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = (res * a) % mod;
        }
        a = a * a % mod;
        b /= 2;
    }
    return res;
}
int cntq1[N], cntl[N], cntr[N], cntq2[N];
ll fac[N], ifac[N];
ll C(ll n, ll m) {
    if (m < 0 || n - m < 0) {
        return 0;
    }
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
int cnt;
int main() {
    cin >> s + 1;
    n      = strlen(s + 1);
    fac[0] = fac[1] = 1;
    for (int i = 1; i <= n; i++) {
        cnt += (s[i] == '?');
        fac[i]   = 1ll * fac[i - 1] * i % mod;
        cntq1[i] = cntq1[i - 1] + (s[i] == '?');
        cntl[i]  = cntl[i - 1] + (s[i] == '(');
    }
    fac[n + 1]  = 1ll * fac[n] * 1ll * (n + 1) % mod;
    ifac[n + 1] = qpow(fac[n + 1], mod - 2);
    ifac[0]     = 1;
    for (int i = n; i >= 1; i--) {
        ifac[i]  = 1ll * ifac[i + 1] * (i + 1) % mod;
        cntr[i]  = cntr[i + 1] + (s[i] == ')');
        cntq2[i] = cntq2[i + 1] + (s[i] == '?');
    }
    ll ans = 0;
    for (int i = 1; i < n; i++) {
        ans = (ans +
               cntl[i] * C(cnt, cntq2[i + 1] + cntr[i + 1] - cntl[i]) % mod) %
              mod;
        ans = (ans + cntq1[i] *
                         C(cnt - 1, cntq2[i + 1] + cntr[i + 1] - cntl[i] - 1) %
                         mod) %
              mod;
    }
    cout << ans;
    return 0;
}
// Asusetic eru quionours
```

