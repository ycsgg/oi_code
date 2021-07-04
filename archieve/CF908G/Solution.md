###　CF908G New Year and Original Order

先做一个奇妙的转化，考虑数字排好序后，比如 $3458$

有四个数大于d等于 $1$ $+1111$ 四个数大于等于 $2$ $+1111$ 四个数大于等于 $3$ $+1111$ 三个数大于 $4$ $+111$

以此类推可以发现所有排好序的数字一定可以写成这个样子

那么我们进需要知道有多少的数字大于等于 $x$ 即可， $x$ 可以枚举

有多少数字可以数位DP $dp_{i,j,0/1}$ 表示 $i$ 个数字 $j$ 个大于等于 $x$ $0/1$ 是是否到上限

```cpp
#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
using ll      = long long;
const int mod = 1e9 + 7;
const int N   = 707;
ll dp[N][N][2];
vector<int> dig;
int len;
ll ans = 0;
ll solve(int x) {
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i <= dig[0]; i++) {
        dp[0][(i >= x)][i == dig[0]]++;
    }
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j <= len - 1; j++) {
            for (int typ = 0; typ <= 1; typ++) {
                auto &val = dp[i][j][typ];
                if (!val)
                    continue;
                int lim = typ ? dig[i + 1] : 9;
                for (int ndig = 0; ndig <= lim; ndig++) {
                    auto &pv =
                        dp[i + 1][j + (ndig >= x)][typ && ndig == dig[i + 1]];
                    pv = (pv + val) % mod;
                }
            }
        }
    }
    ll l11 = 0;
    ll res = 0;
    for (int i = 0; i <= len; i++) {
        res = (res + l11 * (dp[len - 1][i][0] + dp[len - 1][i][1]) % mod) % mod;
        l11 = (l11 * 10 + 1) % mod;
    }
    return res;
}
string s;
signed main() {
    cin >> s;
    dig.resize(s.size());
    len = s.size();
    for (int i = 0; i < s.size(); i++) {
        dig[i] = (s[i] - '0');
    }
    for (int i = 1; i <= 9; i++) {
        ans = (ans + solve(i)) % mod;
    }
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours
```

#数位DP

