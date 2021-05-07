### P6570 [NOI Online #3 提高组] 优秀子序列

把 $a_i$ 拆成二进制，视作一个形如 $\{010010\}$ 的集合，那就是找出所有的不相交的集合的无交并的权值之和

设 $dp_S$ 表示无交并为 $S$  的方案数，答案为 $\sum\limits_{S} dp_S\varphi(S+1)$

容易推出 $dp_S=\sum\limits_{S' \in S}dp_{S'}\times cnt_{S-S'}$，就是选出来子集然后补成集合 $S$

~~可以子集卷积，但没必要~~

好吧还是卷一下

设$F_i(x)=x^{a_i}+x^{\phi}$

卷积为 $(F*G)[k]=\sum\limits_{i|j=k,i\&j=0}F[i]G[j]$

答案就是 $\prod F_i(x)$的系数

按照付公主背包那题套路一下变成

$\exp\sum\ln(x^{a_i}+x^{\phi})=\exp\sum\limits_{i}\sum\limits_{k}\dfrac{(-1)^{k+1}(x^{a_i})^k}{k}$

显然 $(x^{a_i})^k$当且仅当 $k=1$ 时不为零（子集卷积意义下）

所以就是求 $\exp\sum x^{a_i}$

$O(n^2)$ exp即可（没写）

```cpp
#include <iostream>
using namespace std;
const int N = 300005, mod = 1000000007;

int n, mmax, cnt;
int a[N], b[N], dp[N];
int pcnt, primes[N], phi[N];
bool vis[N];

void pre(int n) {
    cnt = 0;
    while ((1 << cnt) <= mmax) {
        ++cnt;
    }
    pcnt   = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) {
            primes[++pcnt] = i;
            phi[i]         = i - 1;
        }
        for (int j = 1; j <= pcnt && primes[j] * i <= n; ++j) {
            vis[primes[j] * i] = 1;
            if (i % primes[j] == 0) {
                phi[primes[j] * i] = phi[i] * primes[j];
                break;
            } else {
                phi[primes[j] * i] = phi[i] * (primes[j] - 1);
            }
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        ++a[x];
        mmax = max(mmax, x);
    }
    pre(N - 1);
    dp[0] = 1, b[0] = 0;
    for (int i = 1; i < (1 << cnt); ++i) {
        b[i] = b[i >> 1] << 1 | 1;
        if (a[i]) {
            int m = b[i] ^ i;
            for (int S = m;; S = (S - 1) & m) {
                dp[S | i] = (dp[S | i] + 1ll * dp[S] * a[i]) % mod;
                if (!S) {
                    break;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < (1 << cnt); ++i) {
        ans = (ans + 1ll * dp[i] * phi[i + 1]) % mod;
    }
    for (int i = 0; i < a[0]; ++i) {
        ans = 2 * ans % mod;
    }
    cout << ans << endl;
}
// Asusetic eru quionours
```

