### P3768 简单的数学题

$$
\large \sum\limits_{i}^n\sum\limits_{j}^n ij\gcd(i,j)
=\sum d\sum\limits_{i}^n\sum\limits_{j}^n ij[\gcd(i,j)=d]\\
\large =\sum d^3\sum\limits_{i}^{\frac{n}{d}}\sum\limits_{j}^{\frac{n}{d}} ij[\gcd(i,j)=1]\\
\large =\sum d^3\sum\limits_{i}^{\frac{n}{d}}\sum\limits_{j}^{\frac{n}{d}} ij\sum\limits_{k|\gcd(i,j)}\mu(k)\\
\large =\sum d^3\sum\limits_{k=1}^{\frac{n}{d}}\mu(k)\sum\limits_{i}^{\frac{n}{kd}}\sum\limits_{j}^{\frac{n}{kd}} ij\\
\large =\sum d^3\sum\limits_{k=1}^{\frac{n}{d}}\mu(k)Sum(\lfloor\frac{n}{kd}\rfloor)
$$

记$T=kd$
$$
\large\sum\limits_{T=1}^nSum(\lfloor\frac{n}{T}\rfloor)T^2\sum\limits_{k|T}\mu(k)\frac{T}{k}\\
\large=\sum\limits_{T=1}^{n}Sum(\lfloor\frac{n}{T}\rfloor)T^2\varphi(T)
$$
对$Sum(\lfloor\frac{n}{T}\rfloor)$数论分块，剩下的$T^2\varphi(T)$是积性的，考虑杜教筛

用一些观察力，用$id^2$卷上去得到$\sum T^2\varphi(T)(\frac{n}{T})^2=n^2\sum\varphi(T)=n^3$

套杜教筛式子$S(n)=\dfrac{\sum\limits_{i=1}^n(f*g)(i)-\sum\limits_{i=2}^{n}g(i)S(\lfloor\frac{n}{i}\rfloor)}{g(1)}$

得到$S(n)=\sum\limits_{i=1}^ni^3-\sum\limits_{i=2}^ni^2S(\lfloor\frac{n}{i}\rfloor)$

然后算

```cpp
#include <cmath>
#include <iostream>
#include <unordered_map>
using namespace std;
typedef long long ll;
const int N = 5e6;
long long n, mod, inv2, inv6, s[N + 2];
int phi[N + 2], prime[N + 1], pcnt, pn;
bool vis[N + 3];
unordered_map<int, ll> s_map;
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
void init() {
    phi[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            phi[i]        = i - 1;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (i * prime[j] > N) {
                break;
            }
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            } else
                phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
    for (int i = 1; i <= N; i++)
        s[i] = (1ll * i * i % mod * phi[i] % mod + s[i - 1]) % mod;
}

ll s3(ll k) {
    k %= mod;
    return (k * (k + 1) / 2) % mod * ((k * (k + 1) / 2) % mod) % mod;
}
ll s2(ll k) {
    k %= mod;
    return k * (k + 1) % mod * (k * 2 + 1) % mod * inv6 % mod;
}
ll calc(ll k) {
    if (k <= N)
        return s[k];
    if (s_map.count(k))
        return s_map[k];
    long long res = s3(k), pre = 1, cur;
    for (ll l = 2, r; l <= k; l = r + 1) {
        r   = k / (k / l);
        res = (res - calc(k / l) * (s2(r) - s2(l - 1) + mod) % mod + mod) % mod;
    }
    s_map[k] = (res + mod) % mod;
    return s_map[k];
}
int main() {
    cin >> mod >> n;
    inv2 = qpow(2, mod - 2), inv6 = qpow(6, mod - 2);
    init();
    ll res = 0, cur, pre = 0;
    for (ll l = 1, r; l <= n; l = r + 1) {
        r   = n / (n / l);
        cur = calc(r);
        res = (res + (s3(n / l) * (cur - pre + mod) % mod) % mod) % mod;
        pre = cur;
    }
    cout << res;
    return 0;
}
```