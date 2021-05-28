### P3706 [SDOI2017]硬币游戏

PGF 入门题，不过套一个高斯消元有点麻烦

考虑单个串的期望(《具体数学》)

比如现在的串是 $THTTH$ ，我们设 $S$ 为目标状态的集合 (THTTH,HTHTTH,TTHTTH.....)

$N$ 为其他状态

显然有 $1+N(H+T)=N+S$

因为 $N$ 后面拼接上一个新的字符要么仍未结束，要么达成目标

一个方程式没法解的，观察串的性质，容易发现

$N\ THTTH=S+S\ TTH$ 成立

这是因为 $TTH$ 所对应的前缀 $TH$ 即使目标串的前缀也是后缀 (border)

所以会导致这种情况的发生

设目标串为 $A$ ，长度为 $m$ 

且 $A_{i}$ 表示串 $A$ 的第 $i$ 个前缀，$A^i$ 表示串 $A$ 的第 $i$ 个后缀

扩展至一般的情况能发现

$1+N(H+T)=N+S$ 必然成立

$NA=S(1+A^1[A^{m-1}=A_{m-1}]+A^2[A^{m-2}=A_{m-2}]+\dots+A^{m-1}[A^1=A_1])$

用生成函数的形式表示出来就是

$N(x)\left({1\over 2}x\right)^m=\sum_{i=1}^m[A^i=A_i]F(x)\left({1\over 2}x\right)^{m-i}$

PGF的一个性质是其在 $1$ 处导数的值及其随机变量的期望

因为 $E(X)=\sum kP(X=k)=\sum P(X=k)kx^{k-1}|_{x=1}$

解方程解得

$E(X)=\sum2^{k-1}[A^k=A_k]$

单串搞定之后多串就好搞了

设 $F_i(x)$ 表示第 $i$ 个串生成函数，意义同单串的 $S(x)$

$G(x)$ 同 $N(x)$

则 $G(x)+\sum F(x)=1+xG(x)$

和 $G(x){(\frac{1}{2}x)}^m=\sum\limits_{i}\sum\limits_{j}[{A}^j={A}_j] F_i(x){(\frac{1}{2}x)}^{m-j}$

(A 默认是第 $i$ 个目标串了，下标打不下了)

大力推柿子 $E(X)=G(1)=\sum\limits_{i}\sum\limits_{j}[{A}^j={A}_j] F_i(1)2^k$

加上 $\sum F(1)=1$ 即可高斯消元

```cpp
#include <cmath>
#include <iostream>
using namespace std;
typedef unsigned long long ull;
const int N      = 305;
const ull base   = 19260817;
const double eps = 1e-8;
ull pw[N], H[N][N];
int n, m;
char s[N];
double eq[N][N];
ull getHash(int x, int l, int r) {
    return H[x][r] - H[x][l - 1] * pw[r - l + 1];
}
bool Eq0(double v) {
    return (v > -eps && v < eps);
}
void Solve(int n) {
    for (int i = 1; i <= n; i++) {
        if (Eq0(eq[i][i])) {
            for (int j = i + 1; j <= n; j++) {
                if (!Eq0(eq[j][i])) {
                    for (int k = i; k <= n + 1; k++) {
                        swap(eq[i][k], eq[j][k]);
                    }
                    break;
                }
            }
        }
        double t = 1.0 / eq[i][i];
        for (int j = i; j <= n + 1; j++) {
            eq[i][j] *= t;
        }
        for (int j = i + 1; j <= n; j++) {
            t = eq[j][i];
            for (int k = i; k <= n + 1; k++) {
                eq[j][k] -= eq[i][k] * t;
            }
        }
    }
    for (int i = n - 1; i >= 1; i--) {
        for (int j = i + 1; j <= n; j++) {
            eq[i][n + 1] -= eq[j][n + 1] * eq[i][j];
        }
    }
}
int main() {
    cin >> n >> m;
    pw[0] = 1;
    for (int i = 1; i <= m; i++) {
        pw[i] = pw[i - 1] * base;
    }
    for (int i = 1; i <= n; i++) {
        cin >> s + 1;
        for (int j = 1; j <= m; j++) {
            H[i][j] = H[i][j - 1] * base + (s[j] == 'H');
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= m; k++) {
                if (getHash(i, 1, k) == getHash(j, m - k + 1, m)) {
                    eq[i][j] += pow(2, k);
                }
            }
            eq[i][n + 1] = -1;
        }
    }
    for (int i = 1; i <= n; i++) {
        eq[n + 1][i] = 1;
    }
    eq[n + 1][n + 2] = 1;
    Solve(n + 1);
    for (int i = 1; i <= n; i++) {
        printf("%.8lf\n", eq[i][n + 2]);
    }
    return 0;
}
// Asusetic eru quionours

```

