### P4451 [国家集训队]整数的lqp拆分

憨憨数学题

设$g_i$是拆分$i$的答案

那么$g_n=\sum g_if_{n-i}+[n=0]$

$f$是斐波那契数列

生成函数$G=G\times F+1$

$G=\frac{1}{1-F}=1-\frac{x}{x^2+2x-1}$

用具体数学的有理根展开

就能得到	$g_n=\frac{\sqrt2-1}{2\sqrt2}(1-\sqrt2)^n+\frac{\sqrt2+1}{2\sqrt2}(1+\sqrt2)^n$

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const ll mod   = 1e9 + 7;
const ll sqrt2 = 59713600;
const ll v1 = (1 - sqrt2 + mod) % mod, v2 = sqrt2 + 1;
const ll c1 = 485071604; // (sqrt(2)-1) / 2sqrt2
const ll c2 = 514928404; // (sqrt(2)+1) / 2sqrt2
ll read() {
    ll x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') {
            f = -1;
        }
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        x %= (mod - 1);
        c = getchar();
    }
    return x * f;
}
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
int main() {
    ll n = read();
    cout << (c1 * qpow(v1, n - 1) % mod + c2 * qpow(v2, n - 1) % mod) % mod;
}
```

