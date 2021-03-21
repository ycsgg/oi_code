### P5176 公约数

$\sum_{i=1}^n\sum_{j=1}^m\sum_{k=1}^p\gcd(i\cdot j,i\cdot k,j\cdot k)\times \gcd(i,j,k)\times \left(\frac{\gcd(i,j)}{\gcd(i,k)\times \gcd(j,k)}+\frac{\gcd(i,k)}{\gcd(i,j)\times \gcd(j,k)}+\frac{\gcd(j,k)}{\gcd(i,j)\times \gcd(i,k)}\right)$

一个结论是$\gcd(ij,ik,jk)=\frac{\gcd(i,j)\gcd(i,k)\gcd(k,j)}{\gcd(i,j,k)}$

拆成唯一分解形式即可证

所以原式为$\sum\limits_{i=1}^n\sum\limits_{j=1}^m\sum\limits_{k=1}^p\gcd(i,j)^2+\gcd(j,k)^2+\gcd(i,k)^k$

虽然看起来是全都是有关的，但其实因为是从$1$到$n$枚举，所以完全可以分开成

$\large p\sum\limits_{i=1}^n\sum\limits_{j=1}^m\gcd(i,j)^2+m\sum\limits_{i=1}^n\sum\limits_{j=1}^p\gcd(i,j)^2+n\sum\limits_{i=1}^p\sum\limits_{j=1}^m\gcd(i,j)^2$ 

考虑里面的$\sum\sum\gcd^2$的求法

大力套路$\sum\limits_{d=1}^nd^2\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{m}{d}\rfloor}[\gcd(i,j)=1]=\sum d^2\sum\limits_{k=1}^{\lfloor\frac{n}{d}\rfloor}\mu(k)\lfloor\frac{n}{dk}\rfloor\lfloor\frac{m}{dk}\rfloor$

枚举$T=dk$

$\sum\limits_{T=1}^n\sum\limits_{k|T}k^2\mu(\frac{T}{k})\lfloor\frac{n}{T}\rfloor\lfloor\frac{m}{T}\rfloor$

而$(ID^2*\mu)$ 显然是积性的 可以筛出来

大力整除分块

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 1000000007;
const int N  = 20000005;
ll f[N];
int prime[N], mu[N], pcnt;
bool vis[N];
void pre(ll lim) {
    f[1] = 1;
    for (ll i = 2; i <= lim; ++i) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            mu[i]         = -1;
            f[i]          = i * i % mod - 1;
        }
        for (ll j = 1; j <= pcnt; ++j) {
            if (prime[j] * i > lim) {
                break;
            }
            vis[i * prime[j]] = true;
            if (i % prime[j])
                f[i * prime[j]] = f[i] * f[prime[j]] % mod;
            else {
                f[i * prime[j]] = f[i] * prime[j] % mod * prime[j] % mod;
                break;
            }
        }
    }
    for (ll i = 2; i <= lim; ++i) {
        f[i] += f[i - 1];
        f[i] %= mod;
    }
}
ll calc(ll n, ll m) {
    if (n > m) {
        swap(n, m);
    }
    ll ans = 0;
    for (ll l = 1, r; l <= n; l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        ans += (f[r] - f[l - 1] + mod) * (n / l) % mod * (m / l) % mod;
        ans %= mod;
    }
    return ans % mod;
}
ll T, n, m, p;
int main() {
    cin >> T;
    pre(N-1);
    while (T-- > 0) {
        cin >> n >> m >> p;
        ll ans = ((n * calc(m, p) % mod + m * calc(n, p) % mod) % mod +
                  p * calc(n, m) % mod) %
                 mod;
        cout << ans << endl;
    }
    return 0;
}
```

