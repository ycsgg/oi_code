### P5153 简单的函数

容易发现$\mathrm{lcm}(1,2,\dots,t-1)|x$且$\mathrm{lcm}(1,2,\dots,t)\nmid x$

那么我们打表前缀$\mathrm{lcm}$的话发现最多$42$个就超过$n$了

并且能够发现$f(x)\in[1,4]$，所以我们统计每一个$f(x)$有多少个即可

考虑对于一个$2\le t\le42$，它的$x$一定是满足$\mathrm{lcm}(1,2,\dots,t-1)|x$且$\mathrm{lcm}(1,2,\dots,t)\nmid x$，也就是$[1,t-1]$的$\mathrm{lcm}$的倍数的个数减去$[1,t]$的

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}
ll _lcm(ll a, ll b) {
    return 1ll * a / gcd(a, b) * b;
}
ll n;
ll f[55];
ll lcm[55];
int pos = 2;
ll cnt[10];
ll calc(ll x) {
    return (1ll * n / x) - (pos / x);
}
ll qpow(ll a, ll b) {
    ll base = a, res = 1;
    while (b) {
        if (b & 1) {
            res = res * base % mod;
        }
        base = base * base % mod;
        b /= 2;
    }
    return res;
}
int main() {
    cin >> n;
    f[2] = 1;
    for (int i = 3; i <= 50; i++) {
        for (int j = 2; j < i; j++) {
            if (i % j != 0) {
                f[i] = f[j] + 1;
                break;
            }
        }
    }
    lcm[1] = 1;
    for (; pos <= 50; pos++) {
        lcm[pos] = _lcm(pos, lcm[pos - 1]);
        if (lcm[pos] > n)
            break;
    }
    for (int i = 2; i <= pos; i++) {
        cnt[f[i] + 1] += calc(lcm[i - 1]) - calc(lcm[i]);
        cnt[f[i]]++;
    }
    ll ans = f[2];
    for (int i = 2; i <= 5; i++) {
        ans = ans * qpow(i, cnt[i]) % mod;
    }
    cout << ans;
    return 0;
}
```