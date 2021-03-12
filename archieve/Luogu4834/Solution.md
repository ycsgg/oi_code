### P4834 萨塔尼亚的期末考试

大概是求$\frac{\sum iF_i}{n(n+1)/2}$

$\sum iF_i=\sum\limits_{i=1}^n\sum\limits_{j=i}^nF_j=\sum\limits_{i=1}^n(\sum\limits_{j=1}^nF_j-\sum\limits_{j=1}^{i-1}F_j)=\sum\limits_{i=1}^nF_{n+2}-F_{i+1}=nF_{n+2}-F_{n+3}+2$

需要矩阵加速

```cpp
#include <algorithm>
#include <cstring>
#include <iostream>
typedef long long ll;
const int mod = 998244353;
using namespace std;
struct Node {
    ll t[3][3];
};
Node res, powmat;
ll ans[3], kkk[3];
int t;
ll qpow(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1)
            ans = x * ans % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return ans;
}
Node Mul(Node x, Node y) {
    Node res;
    for (int i = 1; i <= 2; i++)
        for (int j = 1; j <= 2; j++)
            res.t[i][j] = 0;
    for (int i = 1; i <= 2; i++)
        for (int j = 1; j <= 2; j++)
            for (int k = 1; k <= 2; k++)
                res.t[i][j] =
                    (res.t[i][j] + (x.t[i][k] * y.t[k][j]) % mod) % mod;
    return res;
}
int main() {

    scanf("%d", &t);
    while (t--) {
        ll n;
        memset(ans, 0, sizeof(ans));
        memset(kkk, 0, sizeof(kkk));
        for (int i = 0; i <= 2; i++)
            for (int j = 0; j <= 2; j++)
                powmat.t[i][j] = 0, res.t[i][j] = 0;
        kkk[1] = kkk[2] = 1;
        res.t[1][1] = res.t[2][2] = 1;
        powmat.t[1][1] = powmat.t[1][2] = powmat.t[2][1] = 1;
        cin >> n;
        ll k   = qpow((n * (n + 1) / 2) % mod, mod - 2);
        ll cnt = n + 1;
        while (cnt) {
            if (cnt & 1) {
                res = Mul(res, powmat);
            }
            powmat = Mul(powmat, powmat);
            cnt /= 2;
        }
        for (int i = 1; i <= 2; i++) {
            for (int j = 1; j <= 2; j++) {
                ans[i] = (ans[i] + (kkk[j] * (res.t[i][j]) % mod) % mod) % mod;
            }
        }
        k = k * ((n * ans[2] % mod + mod - (ans[1] % mod) + 2) % mod);
        cout << k % mod << endl;
    }
    return 0;
}
```