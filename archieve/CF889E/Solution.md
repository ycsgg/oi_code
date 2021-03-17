### CF889E Mod Mod Mod

%%%

显然取模是单调不增的，所以取完模最后是$x_n$那么和就是$nx_n+b$，$b$是我们需要确定的最大值（就是超出$x_n$的那部分被取模的和）

设$dp_{i,j}$表示当$\bmod a_i=j$ 的时候最大的$b$，首先是$dp_{i+1,j}=\max\{dp_{i,j}\} \quad (i < a_{i+1})$

同时考虑到因为$[0,j]$中每个值**至少**能够取到$dp_{i,j}$的值（因为只要选择同样的结构）

那么我们把所有的$dp_{i,k}(k\le j)$都看作是$dp_{i,j}$，因为这样一定是可以取到$dp_{i,j}$的，但是比$dp_{i,j}$大的$k$会在$dp_{i,<j}$的部分考虑过

考虑$[0,j]$中的值$\bmod a_{i+1}$会是$0,1,2,\dots,a_{i+1}-1,0,1,2,\dots ,j \bmod a_{i+1}$，设最后一个$\bmod a_{i+1}=a_{i+1}-1$的数字为$m$

考虑在$[m+1,j-1]$这一段，每增加$1$，余数$+1$，所以$j$必然比这个优，而同时与他们余数相同的$[0,j]$中的值肯定也不优

而剩下的$[m-a_{i+1}+j\bmod a_{i+1},m]$这一段通过同样的讨论也可以发现$m$最优

所以只考虑$j \rightarrow j\bmod a_{i+1}$与$m \rightarrow a_{i+1}-1$这两个转移

剩下的转移即为$dp_{i+1,j\bmod a_{i+1}}=\max\{dp_{i,j}+i(j-j\bmod a_{i+1})\}$

与对$m$的转移$dp_{i+1,a_{i+1}-1}=\max\{dp_{i,j}+m-(a_{i+1}-1)\}$

又$m-(a_{i+1}-1)=a_{i+1}\lfloor\frac{j-(a_{i+1}-1)}{a_{i+1}}\rfloor$

因为状态是不满的，每次只多了个$a_{i+1}-1$的状态，或者状态$j\rightarrow j \bmod a_{i+1}$

所以总复杂度为$O(n\log a_{i}\log n)$

值域很大，map优化

```cpp
#include <iostream>
#include <map>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n;
ll mods[N];
ll tmp[N];
map<ll, ll, greater<ll>> dp;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> mods[i];
    }
    dp[mods[1] - 1] = 0;
    for (int i = 1; i < n; i++) {
        int cnt = 0;
        for (auto data : dp) {
            ll j = data.first;
            ll b = data.second;
            if (j < mods[i + 1]) {
                break;
            }
            dp[mods[i + 1] - 1] =
                max(dp[mods[i + 1] - 1],
                    b + (ll)i * (mods[i + 1] * ((j + 1) / mods[i + 1]) -
                                 mods[i + 1]));
            dp[j % mods[i + 1]] =
                max(dp[j % mods[i + 1]], (b + (ll)i * (j - j % mods[i + 1])));
            tmp[cnt++] = j;
        }
        while (cnt--) {
            dp.erase(tmp[cnt]);
        }
    }
    ll ans  = 0;
    ll mmax = 0;
    for (auto i : dp) {
        ans = max(ans, i.first * n + i.second);
    }
    cout << ans << endl;
    return 0;
}
```