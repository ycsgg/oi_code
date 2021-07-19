### P3264 [JLOI2015]管道连接

记 $g_S$ 为**频道**连接状态的最小代价，$f_{x,S}$ 为正常的斯坦纳树的状态，枚举频道状态，然后跑斯坦纳树的转移，最后转移频道 $g_{S}=\max\limits_{T\sub S}g_{T}+g_{S-T}$

```cpp
#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 1005;
int n, m, p;
struct Graph {
    struct Node {
        int v, w;
    };
    vector<Node> edge[N];
    void add(int u, int v, int w) {
        edge[u].emplace_back(Node{v, w});
    }
} G;
struct Data {
    int p, id;
};
queue<int> q;
int vis[N], dp[N][(1 << 10) + 1], g[(1 << 10) - 1];
void SPFA(int S) {
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = 0;
        for (auto e : G.edge[x]) {
            int v = e.v;
            if (dp[v][S] > dp[x][S] + e.w) {
                dp[v][S] = dp[x][S] + e.w;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
}
int main() {
    cin >> n >> m >> p;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G.add(u, v, w);
        G.add(v, u, w);
    }
    vector<Data> qaq(p);
    for (int i = 1; i <= p; i++) {
        cin >> qaq[i].p >> qaq[i].id;
    }
    sort(qaq.begin() + 1, qaq.end(), [&](const auto &A, const auto &B) -> bool {
        return A.p < B.p;
    });
    int cnt = 0;
    for (int i = 1; i <= p; i++) {
        if (qaq[i].p != qaq[i - 1].p) {
            cnt++;
        }
    }
    memset(g, 0x3f, sizeof(g));
    for (int S = 1; S < (1 << cnt); S++) {
        memset(dp, 0x4f, sizeof(dp));
        while (!q.empty()) {
            q.pop();
        }
        int tot = 0;
        for (int i = 1; i <= p; i++) {
            if (S & (1 << (qaq[i].p - 1))) {
                dp[qaq[i].id][1 << tot] = 0;
                tot++;
            }
        }
        for (int U = 1; U < (1 << tot); U++) {
            // cout << U << endl;
            for (int i = 1; i <= n; i++) {
                for (int T = (U - 1) & U; T; T = (T - 1) & U) {
                    dp[i][U] = min(dp[i][U], dp[i][T] + dp[i][U - T]);
                }
                if (dp[i][U] != 0x3f3f3f3f) {
                    q.push(i);
                    vis[i] = 1;
                }
            }
            SPFA(U);
        }

        for (int i = 1; i <= n; i++) {
            g[S] = min(g[S], dp[i][(1 << tot) - 1]);
        }
        // cout << S << " " << g[S] << endl;
        // cout << "------------------" << endl;
    }
    for (int S = 1; S < (1 << cnt); S++) {
        for (int T = (S - 1) & S; T; T = (T - 1) & S) {
            g[S] = min(g[S], g[T] + g[S - T]);
        }
    }
    cout << g[(1 << cnt) - 1];
    return 0;
}
// Asusetic eru quionours
```

