### CF314E Sereja and Squares

其实就是有不同种的括号配对方案数

因为仅需要填右括号，考虑 $dp_{i,j}$ 表示前 $i$ 个里 填了 $j$ 个右括号，答案是 $dp_{n,\dfrac{n}{2}}$

显然 $n$ 是奇数无解

括号种数考虑若有 $x$​ 左括号，那么要填的就有 $\dfrac{n}{2}-x$​ 个左括号，就有 $25^{\dfrac{n}{2}-x}$​ 种方案

```cpp
#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
using uint  = unsigned int;
int n;
char s[N];
uint dp[N];
int main() {
    cin >> n;
    if (n & 1) {
        cout << 0 << endl;
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }
    dp[0]   = 1;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] == '?') {
            for (int j = i / 2; j >= i - n / 2; j--) {
                if (j >= 1)
                    dp[j] += dp[j - 1];
            }
        } else {
            cnt++;
        }
    }
    uint ans = 1;
    for (int i = 1; i <= n / 2 - cnt; i++)
        ans = ans * 25;
    cout << ans * dp[n / 2];
    return 0;
}
// Asusetic eru quionours

```

