### P5504 [JSOI2011] 柠檬

一个比较显然的结论是一段的两个端点一定相同且选定的就是他，不然把不同的拆除去肯定更优

$dp_i\gets \max\limits_{s_i=s_j}\{dp_{j-1}+s_i(c_i-c_j+1)^2\}$

拆开

$dp_i\gets dp_{j-1}+s_ic_i^2-2s_ic_ic_j+s_jc_j^2+2s_ic_i-2s_jc_j+s_i$

变形

$dp_{j-1}+s_jc_j^2-2s_jc_j=2s_ic_ic_j+dp_i-s_ic_i^2-2s_ic_i+s_i$

自变量 $c_j$

斜率 $2s_ic_i$

每个点维护上凸壳即可

```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N = 100005;
using ll    = long long;
array<ll, N> s, cnt, tot, dp;
int n;
vector<ll> st[N];
ll X(int i) {
    return cnt[i];
}
ll Y(int i) {
    return dp[i - 1] + s[i] * cnt[i] * cnt[i] - 2 * s[i] * cnt[i];
}
double slope(int i, int j) {
    return 1.0 * (Y(i) - Y(j)) / (X(i) - X(j));
}
ll calc(int i, int j) {
    return dp[j - 1] + s[i] * (cnt[i] - cnt[j] + 1) * (cnt[i] - cnt[j] + 1);
}
#define top(x) max((int)x.size() - 1, 0)
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        cnt[i] = ++tot[s[i]];
    }
    for (int i = 1; i <= n; i++) {
        int t     = s[i];
        auto &stk = st[t];
        // cout << top(stk) << endl;
        while (top(stk) >= 1 && slope(stk[top(stk) - 1], i) >=
                                    slope(stk[top(stk) - 1], stk[top(stk)])) {
            stk.pop_back();
        }
        st[t].push_back(i);
        while (top(stk) >= 1 &&
               calc(i, stk[top(stk)]) <= calc(i, stk[top(stk) - 1])) {
            stk.pop_back();
        }
        dp[i] = calc(i, stk[top(stk)]);
    }
    cout << dp[n] << endl;
    return 0;
}
// Asusetic eru quionours
```

#斜率优化DP