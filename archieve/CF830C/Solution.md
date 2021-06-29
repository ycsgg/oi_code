###　CF830C Bamboo Partition

数学题

$\sum d-((a_i-1)\bmod d+1)=\sum d-(a_i-d\lfloor\dfrac{a_1-1}{d}\rfloor)=nd-\sum a_i+d\sum\lfloor\dfrac{a_i-1}{d}\rfloor$

若使上式 $\le k$

则 $d\sum(\lfloor\dfrac{a_1-1}{d}\rfloor+1) \le k+\sum a_i$

左边的和式最多只有 $2n\sqrt{\max a_i}$ 种取值 枚举取值然后算出来 $d$ 即可

```cpp
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
int n;
ll k, sum;
int main() {
    cin >> n >> k;
    vector<ll> a(n);
    sum     = k;
    ll mmax = -1;
    for (auto &v : a) {
        cin >> v;
        sum += v;
        mmax = max(mmax, v);
    }
    ll ans = 0;
    for (ll l = 1, r; l <= mmax; l = r + 1) {
        r      = (1ll << 62);
        ll res = 0;
        for (auto x : a) {
            if (x > l) {
                r = min(r, (x - 1) / ((x - 1) / l));
            }
        }
        for (auto x : a) {
            res += (x - 1) / l + 1;
        }
        ll d = sum / res;
        if (d >= l && d <= r) {
            ans = max(ans, d);
        }
    }
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours
```

#数学