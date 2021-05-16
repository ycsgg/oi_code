### CF578D

不算很难搞的数数题

考虑如果是类似 $aaaaaa\dots$ 的串那么随便去一个位置填一个其他字符答案就是 $n(m-1)$

进一步的，如果是类似 $aaabbccc\dots$ 这样的因为相邻的两个同样的字符没有区别，所以每组相邻的相同字符就只有一个 $n(m-1)$ 的贡献

但是想 $aab$ 这样的串 $aa+b$ 和 $ab+a$ 是一样的，拓展一下考虑到 $ababab\dots$ 这样的串所有子串都会被算重一遍，所以统计这样的极长串减掉子串就好

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 1000005;
ll n, m, ans;
char s[N];
int main() {
    cin >> n >> m;
    cin >> s + 1;
    s[0]   = "/QAQ"[0];
    ans    = 1ll * n * (m - 1);
    ll len = 1;
    for (int i = 2; i <= n; i++) {
        if (s[i] != s[i - 1]) {
            ans += n * (m - 1);
            if (len == 1) {
                len++;
                continue;
            }
        }
        if (len != 1) {
            if (s[i] == s[i - 2]) {
                len++;
            } else {
                ans -= len * (len - 1) / 2;
                if (s[i] == s[i - 1]) {
                    len = 1;
                } else {
                    len = 2;
                }
            }
        }
    }
    // cout << len << endl;
    if (len > 1)
        ans -= 1ll * len * (len - 1) / 2;
    cout << ans << endl;
    return 0;
}
//Asusetic eru quionours.
```