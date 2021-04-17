### 二分图最大权完美匹配

KM 算法求解的是二分图最大权完美匹配，但是对于不完美的二分图（点数不等），可以补点达成点数相等的二分图

定义可行顶标 $l(i)$ 是顶点 $i$ 的一个权值，对于所有的边 $u \rightarrow v$ 满足 $w(u,v) \le l(u)+l(v)$

相等边定义为满足 $w(u,v)=l(u)+l(v)$ 的边 $(u,v)$ 同理可以导出相等子图

~~我不会证的~~定理：如果对于某组可行顶标，其相等子图存在完美匹配，则该匹配为原图最大权完美匹配

这样就可以不断更改可行顶标来匹配了

设 $lx(i)$ 为左边 $i$ 的可行顶标 $ly(i)$ 为右边 $i$ 的可行顶标

设初始为 $lx(i)=\max\{w(i,j\},ly(i)=0$

那么跑增广路会跑出来一个树形结构，成为交错树

对于树中的左点 $S$ 与右点 $T$ 与不在树中的点 $S'$ $T'$

在相等子图中有 $S-T'$ 不存在 $S-T'$ 非匹配

给 $S$ 点可行顶标 $+x$ $T$点$-x$

那么 $S-T$ 仍存在在相等子图，$S'-T'$ 无变化， $S-T'$中 $lx+ly$减少，可能加入相等子图，$S'-T$则不可能

所以取 $x=\min\{lx(u)+ly(v)-w(u,v)\}$ 就至少会加入一条新边

$(u,v)$ 加入后若 $v$ 未匹配则有增广路，这样最多修改 $n$ 次即能找到增广路

我们可以直接维护交错树，来算出改变量，一共是$O(n^3)$

```cpp
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int N  = 500;
const ll INF = 2e18;
int n, m;
ll G[N + 7][N + 7];
int linky[N + 7], visy[N + 7];
ll lx[N + 7], ly[N + 7], p[N + 7], slack[N + 7];
void bfs(int u) {
    int x, v = 0, vl = 0, mmin;
    for (int i = 1; i <= n; i++) {
        p[i]     = 0;
        slack[i] = INF;
    }
    linky[v] = u;
    do {
        x = linky[v], mmin = INF, visy[v] = 1;
        for (int y = 1; y <= n; y++) {
            if (!visy[y]) {
                if (slack[y] > lx[x] + ly[y] - G[x][y]) {
                    slack[y] = lx[x] + ly[y] - G[x][y];
                    p[y]     = v;
                }
                if (slack[y] < mmin) {
                    mmin = slack[y];
                    vl   = y;
                }
            }
        }
        for (int y = 0; y <= n; y++) {
            if (visy[y]) {
                lx[linky[y]] -= mmin;
                ly[y] += mmin;
            } else {
                slack[y] -= mmin;
            }
        }
        v = vl;
    } while (linky[v]);
    while (v) {
        linky[v] = linky[p[v]];
        v        = p[v];
    }
}
ll KM() {
    memset(linky, 0, sizeof(linky));
    memset(lx, 0, sizeof(lx));
    memset(ly, 0, sizeof(ly));
    for (int i = 1; i <= n; i++) {
        memset(visy, 0, sizeof(visy));
        bfs(i);
    }
    ll res = 0;
    for (int y = 1; y <= n; y++) {
        res += G[linky[y]][y];
    }
    return res;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            G[i][j] = -INF;
        }
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        G[u][v] = max(G[u][v], w);
    }
    printf("%lld\n", KM());
    for (int i = 1; i <= n; i++) {
        printf("%d ", linky[i]);
    }
    return 0;
}
```

