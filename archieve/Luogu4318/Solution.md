### P4318 完全平方数

排名考虑二分

主要是判断 $[1,n]$ 中有多少个整数是完全平方数的倍数

考虑一个数字不含平方因子就是 等价于 $\mu^2(i)=1$

那么就求 $\sum\mu^2(i)=\sum\sum\limits_{d^2|i}\mu(d)=\sum\limits_i^{\sqrt{n}}\mu(i)\lfloor\dfrac{n}{d^2}\rfloor$

```cpp
#include <array>
#include <iostream>
using namespace std;
const int N = 60010;
using ll    = long long;
array<ll, N> mu, prime;
array<bool, N> vis;
int pcnt;
void pre() {
    mu[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            mu[i]         = -1;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (i * prime[j] >= N) {
                break;
            }
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
}
bool check(ll x, ll k) {
    ll res = 0;
    for (ll i = 1; i * i <= x; i++) {
        res += mu[i] * (x / i / i);
    }
    return res >= k;
}
int T;
int main() {
    pre();
    cin >> T;
    while (T--) {
        ll k;
        cin >> k;
        ll l = k, r = k * 2, ans;
        while (l <= r) {
            ll mid = (l + r) / 2;
            if (check(mid, k)) {
                r   = mid - 1;
                ans = mid;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
// Asusetic eru quionours
```

#数学