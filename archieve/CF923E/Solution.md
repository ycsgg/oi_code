### CF923E Perpetual Subtraction

--update 2021.02.03--

修正二项式反演的一个笔误

#### Solution

设数列$\{f_i^k\}$是第$k$次操作后数字为$i$的概率，考虑到每次rand后数字不可能增大

所以$f_i^{k+1}=\sum\limits_{j=i}^n\dfrac{f_{j}^{k}}{j+1}$，因为每个$f_i^k$都有$[0,i]$一共$i+1$种取值，其中有$\frac{1}{i+1}$概率选到特定的数

对于这种迭代的数列，我们可以考虑他们生成函数间的关系，因为多项式有着优美的性质

设$F_k=\sum x^if_i^k$

那么$F_{k+1}=\sum\limits_{i=0}^nx^i\sum\limits_{j=i}^n\dfrac{f_j^k}{j+1}$

交换求和顺序$\sum\limits_{i=0}^n\dfrac{f_i^k}{i+1}\sum\limits_{j=0}^ix^i=\sum\limits_{i=0}^n\dfrac{f_i^k}{i+1}\dfrac{x^{i+1}-1}{x-1}$等比数列求和一下

提取出无关变量$\dfrac{1}{x-1}\sum\limits_{i=0}^n{f_i^k}(\dfrac{x^{i+1}}{i+1}-\dfrac{1}{i+1})$动用一点观察力能够发现$(\dfrac{x^{i+1}}{i+1}-\dfrac{1}{i+1})=\int^x_0 z^i-\int^1_0z^i=\int^x_1z^i\mathbb{d}z$

所以$F_{k+1}=\dfrac{\int_1^xF_k(z)\mathbb{d}z}{x-1}$

换元设$G_k(x)=F_k(x+1)=\dfrac{1}{x}\int_0^xG_k(z)\mathbb{d}z$，

回顾下生成函数基本操作，能够发现新数列$g_{i}^{k+1}=\dfrac{g_i^k}{i+1}$

$m$次操作仅需$m$次幂即可

然后我们需要快速的从$g_i^k$变成$f_i^k$(为了方便以下省略$k$)

$G=\sum g_ix^i=\sum f_i(x+1)^i=\sum f_i\sum\binom{i}{j}x^i$提取一下

$g_i=\sum\limits_{j=i}^n\binom{j}{i}f_j$

反演一下

$f_i=\sum\limits_{j=i}^n(-1)^{j-i}\binom{j}{i}g_j$

结束啦~~

```cpp
#include "Polynomial.h"
#include <iostream>
using namespace std;
using namespace Poly;
Polynomial<long long> f, g;
const ll Mod   = 998244353;
const int maxn = 1e6 + 7;
typedef long long ll;
ll n, m;
ll fac[maxn], invfac[maxn];
ll a[maxn];
int main() {
    cin >> n >> m;
    n++;
    f.resize(n);
    g.resize(n);
    m %= (Mod - 1);
    fac[0] = 1;
    for (int i = 1; i < n; i++)
        fac[i] = 1ll * fac[i - 1] * i % Mod;
    invfac[n - 1] = invx(fac[n - 1]);
    for (int i = n - 2; i + 1; i--)
        invfac[i] = 1ll * invfac[i + 1] * (i + 1) % Mod;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        f[n - i - 1] = 1ll * fac[i] * a[i] % Mod;
    }
    for (int i = 0; i < n; i++) {
        g[i] = invfac[i];
    }
    f = f * g; // clac g_i^1
    f.resize(n);
    for (int i = 0; i < n; i++) {
        g[i] = 1ll * invfac[i] * f[n - i - 1] % Mod;
    }
    for (int i = 0; i < n; i++) {
        g[i] = 1ll * g[i] * invx(qpow(i + 1, m)) % Mod; // calc g_i^m
    }
    for (int i = 0; i < n; i++) {
        f[n - i - 1] = 1ll * fac[i] * g[i] % Mod;
    }
    for (int i = 0; i < n; i++) {
        g[i] = (i & 1) ? Mod - invfac[i] : invfac[i];
    }
    f = f * g;
    for (int i = 0; i < n; i++) {
        cout << 1ll * invfac[i] * f[n - i - 1] % Mod << " ";
    }
}
```