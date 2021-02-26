### CF204C Little Elephant and Furik and Rubik

https://codeforces.com/problemset/problem/204/C

先推一下式子：

$\large E(F(x,y))=\sum_{x,y} P_i\times F(x,y)$

因为等概率随机，所以所有$P_i$均相等，记作$P$，也就是所有合法的$x,y$的个数

容易发现其实$P=\dfrac{1}{\sum^n_i i^2}=\dfrac{n(n+1)(2*n+1)}{6}$，这里的$n$是字符串产长度

$\large F(x,y)=\sum^{len}_{i=0}[x_i=y_i]$

$\large E(F(x,y))=P\times\sum_{x,y}\sum^{len}_{i=0}[x_i=y_i]$

所以本质上就是求所有子串中相同位置字符一样的个数

那么我们能枚举字符$c$考虑所有$x_i=c$和$y_i=c$的贡献

我们想对于$c$来说如果$x$中有一个位置在$i$，$y$中位置在$j$

那么从$[1,i]$中作为$x$字串起点，$[j,n]$中作为$y$字串结尾都是合法的

假设$i<j$那么贡献就是$i*(n=j+1)$，反之同理

这样的复杂度是$O(n^2)$，可以用前缀后缀和扫一遍来记录两个字符串中的某个字符所带来的贡献

最后累加乘$P$即可

注意会爆$ull$，因为精度只要$10^{-6}$所以用double存

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 200100;
char a[N], b[N];
unsigned long long n;
unsigned long long cnt_forward[27][N], cnt_backward[27][N];
int main() {
    cin >> n;
    cin >> a + 1;
    cin >> b + 1;
    for (int i = 1; i <= n; i++) {
        cnt_forward[a[i] - 'A'][i] = i;
    }
    for (int i = n; i >= 1; i--) {
        cnt_backward[a[i] - 'A'][i] = n - i + 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 26; j++) {
            cnt_forward[j][i] += cnt_forward[j][i - 1];
        }
    }
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j < 26; j++) {
            cnt_backward[j][i] += cnt_backward[j][i + 1];
        }
    }
    double sum = 0;
    for (int i = 1; i <= n;i++){
        char c = b[i] - 'A';
        sum += cnt_forward[c][i] * (n - i + 1);
        sum += cnt_backward[c][i + 1] * i;
    }
    double ans = (double)sum / (double)(n * (n + 1) * (2 * n + 1) / 6.0);
    printf("%.9lf", ans);
    return 0;
}
```



