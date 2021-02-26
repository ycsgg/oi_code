### P3704 [SDOI2017]数字表格

求

$\huge \Pi_{i=1}^n\Pi_{j=1}^mF(gcd(i,j))= \Pi_{d=1}^n\Pi_{i=1}^n\Pi_{j=1}^mF(d)[gcd(i,j)=d]$

套路一波

$\huge \Pi_{d=1}^nF(d)^{\sum_{i=1}^{n/d}\sum_{j=1}^{m/d}[gcd(i,j)=1]}$

继续

$\huge \Pi_{d=1}^nF(d)^{\sum_{i=1}^{n/d}\mu(i)\lfloor{\frac{n}{id}}\rfloor\lfloor{\frac{m}{id}}\rfloor}$

接着套路$T=id$

$\huge\Pi_{T=1}^{n}\Pi_{d|T}F(d)^{\lfloor{\frac{n}{T}}\rfloor\lfloor{\frac{m}{T}}\rfloor\mu(\frac{T}{d})}$

对$d$积

$\huge f(n)=\Pi_{d|n}F(d)^{\mu({\frac{n}{d}})}$

那么要算的就是

$\huge \Pi_{i=1}^{n}f(i)^{\lfloor{\frac{n}{T}}\rfloor\lfloor{\frac{m}{T}}\rfloor}$

$f(i)$硬算，上面的数论分块

$O(\sqrt{n})$

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int N = 1e6, maxn = 1e6 + 5;
ll qpow(ll a, ll b) {
    ll res = 1, base = a;
    while (b) {
        if (b & 1) {
            res = (res * base) % mod;
        }
        base = base * base % mod;
        b /= 2;
    }
    return res;
}
ll inv(ll x) {
    return qpow(x, mod - 2) % mod;
}
ll F[maxn], invF[maxn];
int mu[maxn], prime[maxn], pcnt;
ll f[maxn];
bool vis[maxn];
void Mu() {
    invF[1] = F[1] = 1;
    mu[1]          = 1;
    for (int i = 2; i <= N; i++) {
        F[i]    = (F[i - 1] + F[i - 2]) % mod;
        invF[i] = inv(F[i]);
        if (!vis[i]) {
            prime[++pcnt] = i;
            mu[i]         = -1;
        }
        for (ll j = 1; j <= pcnt; j++) {
            if (prime[j] * i > N) {
                break;
            }
            vis[prime[j] * i] = 1;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            } else {
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
    for (int i = 0; i <= N; i++) {
        f[i] = 1;
    }
    for (int i = 1; i <= N; i++) {
        if (mu[i] == 0)
            continue;
        for (int j = i; j <= N; j += i) {
            f[j] = 1ll * f[j] * ((mu[i] == 1) ? F[j / i] : invF[j / i]) % mod;
        }
    }
    for (int i = 2; i <= N; i++) {
        f[i] = (1ll * f[i] * f[i - 1]) % mod;
    }
}
int t, n, m;
ll calc(ll l, ll r) {
    ll x = 1ll * f[r] * inv(f[l - 1]) % mod;
    return qpow(x, 1ll * (n / l) * (m / l)) % mod;
}
int main() {
    Mu();
    cin >> t;
    while (t--) {
        cin >> n >> m;
        if(n>m){
            swap(n, m);
        }
        ll ans = 1;
        for (int l = 1, r; l <= n; l = r + 1) {
            r   = min(n / (n / l), m / (m / l));
            ans = 1ll * ans * calc(l, r) % mod;
            // cout << calc(l, r) << endl;
        }
        cout << ans << endl;
    }
}
```