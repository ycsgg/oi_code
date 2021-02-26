### CF438E The Child and Binary Tree

http://codeforces.com/contest/438/problem/E

套路题

设$G(x)=\sum_ks_kx^k$,也就是$\{g_i\}$，$i$权值是否被包含

然后设$\{f_i\}$是符合条件的二叉树的个数

那么

$f_i=\sum_i g_i\sum_j f_if_{n-i-j}[n>0]+[n=0]$

是个卷积，套路一波解出来$\{f_i\}$的生成函数$F(x)$

$\large F(x)=\frac{1-\sqrt{1-4G(x)}}{2G(x)}$

然后发现$G(x)$不一定可以求逆

所以可以把逆放下去(分子有理化)

$\large F(x)=\frac{2}{1+\sqrt{1-4G(x)}}$

然后算

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
 //这里是 Poly 板子
namespace Poly{} // namespace Poly
const int N = 4e5 + 5, mod = 998244353;
int n, m;
long long a[N],g[N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[x] = 1;
    }
    g[0] = 1;
    for (int i = 1; i <= m; i++) {
        g[i] = (mod - 4 * a[i] + mod) % mod;
    }
    Poly::Sqrt(g,g,m+1);
    g[0]++;
    Poly::Inv(g,a,m+1);
    for (int i = 1; i <= m;i++){
        cout << a[i] * 2 % mod << endl;
    }
}
```

