### P7516 [省选联考 2021 A/B 卷] 图函数

$f(i,G)$ 就是 $[1,i]$ 这段点里满足 $i \rightarrow x$ 联通且 $x \rightarrow i$ 联通的 $x$ 的个数

发现其实条件就是 存在有 $i \rightarrow x$ 和 $x \rightarrow i$ 的路径不经过 $[1,x)$ 中的点

证明只要口胡下就行，如果存在 $i\rightarrow y \rightarrow x  \ (y \in [1,x)$ 的路径且 $i,x$ 双向联通那 $y$ 就被删了

设 $[i,x]$ 代表满足 $i,x$ 双向联通

那么我们要求的就是当前的 $G$ 的 $\sum\limits_{u,v \in G}[u,v]$

删边不太好做，反向加边

随着边增加满足条件的点对必然增大，仅需求出增量然后前缀和就行，也就是找到每个点对最早满足条件的时间

这种转移直接 Floyd 即可

复杂度 $O(n^3+m)$，虽然看起来稳 T 但是能过...

```cpp
#include <iostream>
using namespace std;
const int N = 1005;
int G[N][N];
int tim[N * N];
int n, m, ans[N * N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G[u][v] = i;
    }
    for (int k = n; k >= 1; k--) {
        for (int i = k + 1; i <= n; i++) {
            tim[min(G[k][i], G[i][k])]++;
        }
        for (int i = 1; i <= n; i++) {
            if (!G[i][k]) {
                continue;
            }
            int nowid = G[i][k];
            if (i > k) {
                for (int j = 1; j < k; j++) {
                    G[i][j] = max(G[i][j], min(nowid, G[k][j]));
                }
            } else {
                for (int j = 1; j <= n; j++) {
                    G[i][j] = max(G[i][j], min(nowid, G[k][j]));
                }
            }
        }
    }
    ans[m + 1] = n;
    for (int i = m; i >= 1; i--) {
        ans[i] = ans[i + 1] + tim[i];
    }
    for (int i = 1; i <= m + 1; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}

```

**Asusetic eru quiounours**