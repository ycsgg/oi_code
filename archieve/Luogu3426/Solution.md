### P3426 [POI2005]SZA-Template

如果一个章能印完一个字符串必然是它的一个 border

考虑 $dp_i$ 表示前 $i$ 个字符的答案，显然要么是 $i$ 要么是 $dp_{nxt_i}$

但是 $abaaab$ 这样的就有可能转移不到$nxt_i$

思考一下发现必须要存在有一个点 $x$ 使得 $dp_x=dp_{nxt_i}$ 且 $x$ 在最后的 $nxt_i$ 的一段中，即 $x \in [i-nxt_i,i]$

```cpp
#include <cstring>
#include <iostream>
using namespace std;
const int N = 500005;
int n;
char s[N];
int nxt[N];
int dp[N];
int pos[N];
int main() {
    cin >> s + 1;
    n      = strlen(s + 1);
    nxt[0] = -1;
    nxt[1] = 0;
    dp[1]  = 1;
    pos[1] = 1;
    int j  = 0;
    for (int i = 2; i <= n; i++) {
        dp[i] = i;
        while (j != -1 && s[j + 1] != s[i]) {
            j = nxt[j];
        }
        ++j;
        nxt[i] = j;
    }
    for (int i = 2; i <= n; i++) {
        if (pos[dp[nxt[i]]] >= i - nxt[i]) {
            dp[i] = min(dp[i], dp[nxt[i]]);
        }
        pos[dp[i]] = i;
    }
    cout << dp[n];
    return 0;
}
// Asusetic eru quionours
```

