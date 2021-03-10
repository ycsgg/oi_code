### P4450 双亲数

$\large \sum\limits_{1\le a \le A}\sum\limits_{1\le b \le B}[gcd(a,b)=d]$

$\large=\sum\limits_{1\le a\le\lfloor\frac{A}{d}\rfloor}\sum\limits_{1\le b\le\lfloor\frac{B}{d}\rfloor}[gcd(a,b)=1]$

$\large=\sum \mu(k)\sum\limits_{1\le a\le\lfloor\frac{A}{dk}\rfloor}\sum\limits_{1\le b\le\lfloor\frac{B}{dk}\rfloor}$

$\large=\sum\mu(k)\lfloor\frac{A}{kd}\rfloor\lfloor\frac{B}{kd}\rfloor$

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
ll A, B, d;
int prime[N], pcnt;
ll mu[N];
bool vis[N];
void pre() {
    mu[1] = 1;
    for (int i = 2; i <= A; i++) {
        if (!vis[i]) {
            mu[i]         = -1;
            prime[++pcnt] = i;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (prime[j] * i > A)
                break;
            vis[prime[j] * i] = 1;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            } else {
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
    for (int i = 2; i <= A; i++) {
        mu[i] = mu[i - 1] + mu[i];
    }
}
long long ans = 0;
int main() {
    cin >> A >> B >> d;
    A /= d;
    B /= d;
    if (A > B) {
        swap(A, B);
    }
    pre();
    for (int l = 1, r; l <= A; l = r + 1) {
        r = min(A / (A / l), B / (B / l));
        ans += (A / l) * (B / l) * (mu[r] - mu[l - 1]);
    }
    cout << ans;
    return 0;
}
```