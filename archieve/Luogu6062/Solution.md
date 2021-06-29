### P6062 [USACO05JAN]Muddy Fields G

一个显然的事实是木板一定要覆盖能覆盖的最大面积

那么把横纵的所有极长区间找出来连边跑二分图最大匹配即可

```cpp
#include <array>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 55;
int n, m;
int mp[N][N], id1[N][N], id2[N][N], idcnt, link[N * N * 2];
bool G[N * N * 2][N * N * 2], vis[N * N * 2];
int tot;
bool match(int x) {
    for (int i = tot + 1; i <= idcnt; i++) {
        if (G[x][i] && !vis[i]) {
            vis[i] = 1;
            if (!link[i] || match(link[i])) {
                link[i] = x;
                return 1;
            }
        }
    }
    return 0;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            mp[i][j + 1] = (s[j] == '*');
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mp[i][j]) {
                if (!mp[i][j - 1]) {
                    id1[i][j] = ++idcnt;
                } else {
                    id1[i][j] = idcnt;
                }
            }
        }
    }
    tot = idcnt;
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            if (mp[i][j]) {
                if (!mp[i - 1][j]) {
                    id2[i][j] = ++idcnt;
                } else {
                    id2[i][j] = idcnt;
                }
                G[id1[i][j]][id2[i][j]] = 1;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= tot; i++) {
        memset(vis, 0, sizeof(vis));
        ans += match(i);
    }
    cout << ans << endl;
    return 0;
}
// Asusetic eru quionours
```

#二分图最大匹配