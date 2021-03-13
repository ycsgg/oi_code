### P3175 [HAOI2015]按位或

Min-Max容斥：
$$
\max(S)=\sum\limits_{T\in S}(-1)^{|T|+1}\min(T)\\
\min(S)=\sum\limits_{T\in S}(-1)^{|T|+1}\max(T)\\
$$
证明的话考虑仅有$\min(\max(S))$是$\max(S)$，并且他系数为$1$，同时考虑其他的值$a$，排名为$k$，那么$\min(T)=a$当且仅当选出的集合是后$n-k$个元素的集合的子集并上$\{a\}$得到的，这样的集合有$2^{n-k}$种，奇数大小有$2^{n-k-1}$种，偶数同样，所以被消掉了



所以$E(\max(S))=\sum\limits_{T\in S}(-1)^{|T|+1}E(\min(T))$

因为我们没办法知道两个位置变成$1$的期望大小，所以只能动用Min-Max这种暴力的东西，现在我们需要求$E(\min(T))$

也就是集合$T$中至少有一个变成了$1$的期望数，可知$P(\min(T)=k)=P(S\oplus T)^{k-1}(1-P(S\oplus T))$

也就是前$k-1$次都没选中$T$中的数字，这个是一个系数为$1-P(S\oplus T)$的几何分布

对于$P(T)$可以FMT搞定

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const double eps = 1e-8;
int n, cnt[1 << 21], LIM;
double P[1 << 21], ans;
int main() {
    cin >> n;
    LIM = 1 << n;
    for (int i = 0; i < LIM; ++i) {
        cin >> P[i];
        cnt[i] = cnt[i >> 1] + (i & 1);
    }
    for (int i = 1; i < LIM; i <<= 1) {
        int p = i << 1;
        for (int j = 0; j < LIM; j += p) {
            for (int k = 0; k < i; ++k) {
                P[i + j + k] += P[j + k];
            }
        }
    }
    for (int i = 1; i < LIM; ++i) {
        if (1 - P[(LIM - 1) ^ i] > eps) {
            ans += ((cnt[i] & 1) ? 1 : -1) / (1 - P[(LIM - 1) ^ i]);
        }
    }
    if (ans < 1e-10)
        cout << "INF" << endl;
    else
        printf("%.10lf\n", ans);
    return 0;
}
```