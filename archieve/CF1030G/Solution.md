### CF1030G Linear Congruential Generator

~~翻学长的题单翻到了奇怪标签的题~~

#### Solution

因为每个点都是在$\bmod p_i$意义下进行的运算，所以直觉上最多$p_i$次后一定会出现循环，但是不一定是纯循环，可能会有一个留下的“柄”，如果记每一个“柄”的长度为$l_i$，循环长度为$c_i$，那最终答案是$max(l_i)+lcm(c_i)$

我们细致的考察一下这个循环关系

##### I. $a_i=0$

最简单的情况，$c_i=1$，当$x_i=b_i$时候$l_i=0$，否则$l_i=1$

##### II $a_i=1$

此时$f_i^{(k)}=(x_i+(k-1)b_i)\bmod p_i$，$l_i=0$当$b_i=0$时$c_i=1$，否则$c_i=p_i$

##### III otherwise

$a_i>1$，因为$p_i$是质数，所以$a_i^{-1},(a_i-1)^{-1}$均存在，那么就一定能回来，所以$l_i=0$

既然$l_i=0$了，那么$x_i\equiv a_i^{c_i}x_i+b_i\sum_{j=0}^{k-1}a_i^j\equiv x_i\equiv a_i^{c_i}x_i+b_i(a_i^{c_i}-1)(a_i-1)^{-1} \bmod p_i$

即$(a_i^{c_i}-1)\left(x_i+b_i(a_i-1)^{-1}\right) \equiv 0 \bmod p_i$

也即$(a^{c_i}-1)\equiv0$或$\left(x_i+b_i(a_i-1)^{-1}\right) \equiv 0$

第二个式子与$c_i$无关，所以$c_i=1$，考虑到$c_i$需要求$lcm$所以这样一定不优

第一个式子中的$c_i$就是$a_i$关于$p_i$的阶，即$c_i=p_i-1$

##### 最后

整理一下

$a_i=0 \Rightarrow l_i=1，c_i=1$

$a_i=1 \Rightarrow l_i=0，c_i=p_i$

$a_i>1 \Rightarrow l_i=0，c_i=p_i-1$

现在我们需要决定一组$a_i$，最大化$max(l_i)+lcm(c_i)$

直觉上因为$l_i\le1$，所以最大化$lcm$是比较优的，所以我们可以先考虑最大化$lcm$，然后看看能不能选$1$(因为每去一个因子$lcm$至少除二，所以损失lcm换$l_i$是亏的)

最大化$lcm$是很容易的，降序考虑每个$p_i$，如果当前的$lcm$包含了$p_i$，就选择$a_i>1$否则选择$a_i=1$

同时记录下$lcm$每个质因子的最高次幂被几个$c_i$达到了，检查选择的$c_i$，如果有一个$c_i$的全部质因子都被达到不止一次，那就选上一个$1$

```cpp
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
const int N   = 2000005;
const int mod = 1000000007;
ll p[N];
int max_p[N], cnt[N];
int prime[555555], pcnt;
bool pvis[N];
int n;
void getP(int n) {
    for (int i = 2; i <= n; i++) {
        if (!pvis[i]) {
            prime[++pcnt] = i;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (prime[j] * i > n)
                break;
            pvis[prime[j] * i] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}
ll qpow(int a, int k) {
    ll res = 1, base = a;
    while (k) {
        if (k & 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        k /= 2;
    }
    return res;
}
inline void update(int p, int k) {
    if (k > max_p[p]) {
        max_p[p] = k;
        cnt[p]   = 1;
    } else if (k == max_p[p]) {
        ++cnt[p];
    }
}
bool check(int x) {
    if (pvis[x]) {
        for (int i = 1; i <= pcnt; i++) {
            if (prime[i] * prime[i] > x) {
                break;
            }
            int k = 0;
            while (x % prime[i] == 0) {
                x /= prime[i];
                k++;
            }
            if (max_p[prime[i]] == k && cnt[prime[i]] == 1) {
                return false;
            }
        }
        if (x > 1 && max_p[x] == 1 && cnt[x] == 1)
            return false;
        return true;
    } else {
        if (max_p[x] == 1 && cnt[x] == 1)
            return false;
        return true;
    }
}
ll lcm  = 1;
int nya = 3;
bool vis[N];
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
    }
    sort(p + 1, p + n + 1);
    getP(p[n]);
    for (int i = n; i >= 1; i--) {
        if (max_p[p[i]]) {
            int val = p[i] - 1;
            for (int j = 1; j <= pcnt; j++) {
                if (prime[j] * prime[j] > val)
                    break;
                int k = 0;
                while (val % prime[j] == 0) {
                    val /= prime[j];
                    k++;
                }
                k != 0 ? update(prime[j], k) : (void)nya;
            }
            if (val > 1) {
                update(val, 1);
            }
            vis[i] = 1;
        } else {
            update(p[i], 1);
        }
    }
    for (int i = 1; i <= pcnt; i++) {
        if (max_p[prime[i]]) {
            lcm = 1ll * lcm * qpow(prime[i], max_p[prime[i]]) % mod;
        }
    }
    for (int i = 1; i <= n; i++) {
        if ((vis[i] && check(p[i] - 1)) || (!vis[i] && check(p[i]))) {
            lcm = (lcm + 1) % mod;
            break;
        }
    }
    cout << lcm;
}
```

