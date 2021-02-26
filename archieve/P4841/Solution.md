### P4841 [集训队作业2013]城市规划

（先感谢command_block神仙的计数原理

计数原理入门，考虑到连通图是一般图的基本元素，那么连通图的$exp$就是一般图

而一般图的方案是非常好求的，也即$\large 2^{\binom{i}{2}}$

取$ln$即可

```cpp
#include "Polynomial.h"
using namespace Poly;
using namespace std;
Polynomial<long long> f;
const int maxn = 4e5 + 5;
long long fac[maxn];
int n;
int main() {
    cin >> n;
    f.resize(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    for (int i = 0; i <= n; i++) {
        f[i] = qpow(2, 1ll * i * (i - 1) / 2) * qpow(fac[i], mod - 2) % mod;
    }
    cout << 1ll * fac[n] * Ln(f)[n] % mod;
}
```