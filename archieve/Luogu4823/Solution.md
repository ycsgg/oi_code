### P4823 [TJOI2013]拯救小矮人

类似国王游戏，按照 $a+b$ 排序

一定是小的先跑出去，确定了顺序设 $dp_{i,j}$ 表示当前第 $i$ 个跑了 $j$ 个的最大高度，类似背包的转移即可

$i$ 可以滚动

```cpp
#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 2005;
struct Data {
    int a, b;
};
int n, H;
int dp[N];
int main() {
    cin >> n;
    vector<Data> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i].a >> a[i].b;
    }
    sort(a.begin() + 1, a.end(), [&](const auto &A, const auto &B) -> bool {
        return (A.a + A.b) < (B.a + B.b);
    });
    cin >> H;
    memset(dp, -0x3f, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[0] += a[i].a;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i; j >= 1; j--) {
            if (dp[j - 1] + a[i].b >= H) {
                dp[j] = max(dp[j], dp[j - 1] - a[i].a);
            }
        }
    }
    for (int i = n; i >= 0; i--) {
        if (dp[i] >= 0) {
            cout << i << endl;
            return 0;
        }
    }
    return 0;
}
// Asusetic eru quionours
```

#DP