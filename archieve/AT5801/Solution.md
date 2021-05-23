### AT5801 [AGC043D] Merge Triplets

 一堆三元组是没法数的，肯定得直接数生成的序列

考虑每个三元组长度为 $3$ ~~(废话)~~ ，最终排列中不可能有某个数字大于后面的连续的三个数字

因为考虑下一个拿出来的数字如果比他小肯定是因为这是他所在的三元组的下一个被拿出来了，所以不可能多于三个

那我们对于这个数列取前缀 $\max$ ，相同的段必然不超过三，这是个挺强的条件

但是不够充分

思考原来的结构，长度为 $3$ 的段就是把整个三元组选上，感觉不成问题

长度为 $2$ 的段不能是一个三元组，必须要加一个长度为 $1$ 的段拼起来

所以长度为 $2$ 的段必须小于等于长度为 $1$ 的段，又因为整个序列是 $3N$ 的，剩下的零散 $1$ 段必然能拼成三元组

所以这就是充要条件

设 $dp_{i,j,k}$ 表示 $1 \dots i$ 排列中有 $j$ 个长度为 $1$ 的段，$k$ 个长度为 $2$ 的段，转移 $O(n^3)$ 不能接受，但是其实记录有多少个 $1$ $2$ 是没意义的

那设 $dp_{i,j}$ 为 $1\dots i$ 的排列中长度为 $1$ 的段减去长度为 $2$ 的段差为 $j$ 的方案

进行转移的话就是

$dp_{i+1,j+1}=dp_{i,j}$ 加入新 $1$ 段

$dp_{i+2,j-1}=(i+1)dp_{i,j}$ 加入新 $2$ 段

$dp_{i+3,j}=(i+1)(i+2)dp_{i,j}$ 加入新 $3$ 段

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const int N    = 2005;
const int Offset = N * 3;
ll mod;
int n;
ll dp[N * 3][N * 6];
int main() {
    cin >> n >> mod;
    dp[0][0 + Offset] = 1;
    for (int i = 0; i < n * 3; i++) {
        for (int j = -i; j <= i; j++) {
            dp[i + 1][j + 1 + Offset] += dp[i][j + Offset];
            dp[i + 1][j + 1 + Offset] %= mod;
            dp[i + 2][j - 1 + Offset] += dp[i][j + Offset] * (i + 1) % mod;
            dp[i + 2][j + 1 + Offset] %= mod;
            dp[i + 3][j + Offset] +=
                1ll * dp[i][j + Offset] * (i + 1) % mod * (i + 2) % mod;
            dp[i + 3][j + 1 + Offset] %= mod;
        }
    }
    ll ans = 0;
    for (int i = 0; i <= n * 3; i++) {
        ans += dp[n * 3][i + Offset];
        ans %= mod;
    }
    cout << ans;
    return 0;
}
// Asusetic eru quionours
```

