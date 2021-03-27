### P7469 [NOI Online 2021 提高组] 积木小赛

大水题，赛时nt看错题算的能构成合法子串的的子序列方案数

希望未来别出nt事故，不然真就凉透了.....

就扫出来每一个字串然后贪心匹配子序列，hash判重

```cpp
#include <iostream>
#include <vector>
using namespace std;
typedef unsigned long long ull;
const ull base = 20050207, mod = 1145141;
int n, ans;
char s[3001], t[3001];
ull Hash[3001][3001];
vector<ull> table[mod];
bool check(int l, int r) {
    int gH    = Hash[l][r] % mod;
    bool flag = 0;
    for (auto d : table[gH]) {
        if (Hash[l][r] == d) {
            flag = 1;
            break;
        }
    }
    if (flag) {
        return false;
    }
    table[gH].push_back(Hash[l][r]);
    return true;
}
int main() {
    cin >> n;
    scanf("%s%s", s + 1, t + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            Hash[i][j] = Hash[i][j - 1] * base + t[j] - 'a' + 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        int pos = 1;
        for (int j = i, pos = 1; j <= n; j++) {
            while (pos <= n && s[pos] != t[j]) {
                pos++;
            }
            if (pos > n)
                break;
            if (check(i, j)) {
                ans++;
            }
            ++pos;
        }
    }
    cout << ans;
    return 0;
}
```

