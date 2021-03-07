### P5221 Product



$$
\prod\prod\frac{\mathrm{lcm}(i,j)}{\gcd(i,j)}=\prod\prod\frac{ij}{\gcd(i,j)^2}=\prod\prod ij \prod\prod\gcd(i,j)^{-2}=(n!)^{2n}\prod\prod\gcd(i,j)^{-2}
$$

$$
\prod\prod\gcd(i,j)=\prod\limits_{d}\prod\prod [\gcd(i,g)=d]=\prod\limits_{d}d^{\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}[\gcd(i,j)=1]}
$$

指数上的就是欧拉函数前缀和

所以原式就是$\large(n!)^{2n}(\prod\limits_{d}d^{2\sum\varphi(\frac{n}{d})-1})^{-2}$

指数部分需要用欧拉定理优化

```cpp
#include <iostream>
using namespace std;
const int N   = 1000000 + 5;
const int mod = 104857601;
int n;
bool vis[N];
int prime[80001], phi[N], pcnt;
long long res = 1, ans = 1;
long long qpow(long long a, int b) {
    long long res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b /= 2;
    }
    return res;
}
void pre(int x) {
    phi[1] = 1;
    for (int i = 2; i <= x; i++) {
        res = 1ll * res * i % mod;
        if (!vis[i]) {
            prime[++pcnt] = i;
            phi[i]        = i - 1;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (prime[j] * i > x) {
                break;
            }
            vis[prime[j] * i] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
}
int main() {
    cin >> n;
    pre(n);
    for (int i = 1; i <= n; i++) {
        phi[i] = (phi[i] * 2 + phi[i - 1]) % (mod - 1);
    }
    res = qpow(res, 2 * n);
    for (int i = 2; i <= n; i++) {
        ans = 1ll * ans * qpow(i, phi[n / i] - 1) % mod;
    }
    ans = 1ll * res * qpow(ans, mod - 3) % mod;
    cout << ans;
    return 0;
}
```