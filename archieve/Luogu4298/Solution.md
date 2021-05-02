### P4298 [CTSC2008]祭祀

三问毒瘤

第一问就是裸的 Diliworth 跑最小链覆盖即可

第二问考虑二分图的最小点覆盖去掉就可

第三问就直接删点和连边，如果删之后的最大反链减少了 $1$ 说明这个点可以选

证明略~~不会~~

```cpp
#include <cstring>
#include <iostream>
using namespace std;
const int N = 105;
int n, m;
bool G[N][N], tmpG[N][N];
int vis[N], idvis;
int link[N], rlink[N];
bool del[N];
bool dfs(int x) {
    if (del[x]) {
        return false;
    }
    for (int i = 1; i <= n; i++) {
        if (G[x][i] && vis[i] != idvis) {
            vis[i] = idvis;
            if (!link[i] || dfs(link[i])) {
                link[i]  = x;
                rlink[x] = i;
                return true;
            }
        }
    }
    return false;
}
bool r[N], l[N];
void solve(int x) {
    if (r[x]) {
        return;
    }
    r[x] = 1;
    for (int i = 1; i <= n; i++) {
        if (G[x][i] && !l[i]) {
            l[i] = 1;
            solve(link[i]);
        }
    }
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G[u][v] = 1;
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                G[i][j] |= (G[i][k] & G[k][j]);
            }
        }
    }
    memcpy(tmpG, G, sizeof(G));
    int ans = n;
    for (int i = 1; i <= n; i++) {
        idvis++;
        ans -= dfs(i);
    }
    cout << ans << endl;
    for (int i = 1; i <= n; i++) {
        if (!rlink[i]) {
            solve(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << (!l[i] && r[i]);
    }
    cout << endl;
    for (int x = 1; x <= n; x++) {
        memset(link, 0, sizeof(link));
        memset(rlink, 0, sizeof(rlink));
        int cnt = 0;
        memset(G, 0, sizeof(G));
        memset(del, 0, sizeof(del));
        for (int i = 1; i <= n; i++) {
            if (tmpG[i][x] || tmpG[x][i] || x == i) {
                del[i] = 1;
            } else {
                ++cnt;
            }
        }
        int res = cnt;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                G[i][j] = (tmpG[i][j] && !del[i] && !del[j]);
            }
        }
        for (int i = 1; i <= n; i++) {
            if (!del[i]) {
                ++idvis;
                res -= dfs(i);
            }
        }
        cout << (res == ans - 1);
    }
    return 0;
}
// Asusetic eru quionours
```