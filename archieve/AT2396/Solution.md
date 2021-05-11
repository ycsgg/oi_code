### AT2396 [ARC071D] Infinite Sequence

考虑如果有两个相邻的数字都不是 $1$ 那么就无限套娃下去了，即 $abbb\dots$

从这个方向下手设 $dp_i $ 是 $[i,n]$ 填完的方案数

那当 $i$ 填 $1$ 就是 $dp_i+=dp_{i+1}$

如果是无限套娃那这两个位从 $[2,n]$ 里随便填 $dp_i+=(n-1)^2$

当 $i$ 填非 $1$ 但是 $i+1$ 填 $1$ 就是 $a\underbrace{111\dots}_ablabla$

所以对于每一个选择 $x$ 就是 $dp_{i}+=dp_{i+x+1}$

初始值 $dp_n=n,dp_{n-1}=n^2$

然后后缀和优化

```cpp
#include <iostream>
using namespace std;
const int N = 1000010;
typedef long long ll;
const ll mod = 1e9 + 7;
ll dp[N];
ll sum;
ll n;
int main() {
    cin >> n;
    dp[n]     = n;
    dp[n - 1] = (n * n) % mod;
    for (int i = n - 2; i >= 1; i--) {
        sum += dp[i + 3];
        sum %= mod;
        dp[i] = dp[i + 1];
        dp[i] += (n - 1) * (n - 1) % mod;
        dp[i] %= mod;
        dp[i] += sum;
        dp[i] %= mod;
        dp[i] += i + 1 % mod;
        dp[i] %= mod;
    }
    cout << dp[1] % mod;
    return 0;
}
// Asusetic eru quionours
```