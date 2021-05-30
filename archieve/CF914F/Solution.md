### 	CF914F Substrings in a String

$O(\frac{qn}{\omega})$ 吊打 $O(n\sqrt n)$ ...

待修改的字符串匹配，看起来完全没办法做

用 Bitset 维护每个字母出现的位置

每次匹配子串的时候，找到文本串中的所有当且模式串某一位的字符出现的位置，然后全都与在一起

例如 $abbaaba \rightarrow 1001101(a) \ 0110010(b)$ 

匹配 $ab$ 的时候 $a\rightarrow 1001101$ $b\rightarrow 1100100$ （左移是为了和上一位的匹配位置对齐

最终出现位置 $1000100$

这样最终剩下的 $1$ 的个数就是匹配数量

复杂度不对？但是他确实跑的飞快还没卡掉

```cpp
#include <bitset>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e5 + 5;
bitset<N> p[28], res;
char s[N], tmp[N];
int n;
int main() {
    cin >> s + 1;
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        p[s[i] - 'a'].set(i);
    }
    int q;
    cin >> q;
    while (q--) {
        int opt, pos, l, r;
        cin >> opt;
        if (opt == 1) {
            char c;
            cin >> pos >> c;
            p[s[pos] - 'a'].reset(pos);
            s[pos] = c;
            p[s[pos] - 'a'].set(pos);
        } else {
            cin >> l >> r >> tmp + 1;
            int len = strlen(tmp + 1);
            res.set();
            r = r - len + 1;
            for (int i = 1; i <= len; i++) {
                res &= p[tmp[i] - 'a'] >> (i - 1);
            }
            int lcnt = (res >> l).count();
            int rcnt = (res >> (r + 1)).count();
            cout << max(lcnt - rcnt, 0) << endl;
        }
    }
    return 0;
}
// Asusetic eru quionours
```

