### P4037 [JSOI2008]魔兽地图

挺麻烦的

设状态为 $dp[i][j][k]$ 表示 $i$ 号装备用 $j$ 个合成花费 $k$ 元

叶子直接处理

其他节点枚举合成几个，然后遍历儿子节点分组背包dp一下最大的力量

然后用背包去更新 $dp$

同样再枚举合成几个

```cpp
#include <cstring>
#include <iostream>
using namespace std;
const int N = 105;
const int M = 2005;
const int K = 105;
int dp[N][K][M];
int val[N], cnt[N], cost[N];
int ans[M];
struct Edge {
    int v;
    int w, nxt;
} edge[N * 10];
int head[N * 2], ecnt;
void add(int u, int v, int w) {
    edge[++ecnt].v = v;
    edge[ecnt].w   = w;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
int n, m;
bool in[N], leaf[N];
int lim[N], g[M];
void dfs(int x) {
    if (leaf[x]) {
        lim[x] = min(cnt[x], m / cost[x]);
        for (int i = lim[x]; i >= 0; i--) {
            for (int j = i; j <= lim[x]; j++) {
                dp[x][i][j * cost[x]] = val[x] * (j - i);
            }
        }
        return;
    }
    lim[x] = 0x7f7f7f7f;
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        dfs(v);
        lim[x] = min(lim[x], lim[v] / edge[i].w);
        cost[x] += edge[i].w * cost[v];
    }
    lim[x] = min(lim[x], m / cost[x]);
    for (int t = lim[x]; t >= 0; t--) {
        memset(g, -0x3f, sizeof(g));
        g[0] = 0;
        for (int i = head[x]; i; i = edge[i].nxt) {
            int v = edge[i].v;
            for (int qm = m; qm >= 0; qm--) {
                int p = -1e9;
                for (int b = 0; b <= qm; b++) {
                    p = max(p, g[qm - b] + dp[v][t * edge[i].w][b]);
                }
                g[qm] = p;
            }
        }
        for (int i = 0; i <= t; i++) {
            for (int k = 0; k <= m; k++) {
                dp[x][i][k] = max(dp[x][i][k], g[k] + val[x] * (t - i));
            }
        }
    }
}
int main() {
    memset(dp, -0x3f, sizeof(dp));
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
        char typ;
        cin >> typ;
        if (typ == 'A') {
            int c;
            cin >> c;
            while (c--) {
                int v, w;
                cin >> v >> w;
                add(i, v, w);
                in[v] = 1;
            }
        } else {
            cin >> cost[i] >> cnt[i];
            leaf[i] = 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!in[i]) {
            dfs(i);
            for (int j = m; j >= 0; j--) {
                for (int k = 0; k <= j; k++) {
                    ans[j] = max(ans[j], ans[j - k] + dp[i][0][k]);
                }
            }
        }
    }
    cout << ans[m];
    return 0;
}
// Asusetic eru quionours
```

