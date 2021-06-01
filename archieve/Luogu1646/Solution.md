### P1646 [国家集训队]happiness

最小割

源点 $s$ 代表文科，汇点 $t$ 代表理科

所有人先向文理连边

对于两个人同时选文科的权值，新建一个点 $x$ ，从 $s$ 向 $x$ 连权值的边，$x$ 向两人连 $\infty$ 的边，理科同理

一个人如果选文它向理科的边就要断，向理科间接连的中间点也得断，但是不能断 $\infty$ 的边，只能断同时选的边

这样跑出来的最小割一定是最少的愉悦值损失，用总数减掉即可

```cpp
#include <cstring>
#include <iostream>
#include <queue>
#include <cstdio>
using namespace std;
const int INF = 0x7f7f7f7f;
const int N   = 105 * 105 * 10;
struct Edge {
    int v;
    int w, nxt;
} edge[N * 10];
int head[N], ecnt = 1, cur[N];
void _add(int u, int v, int w) {
    edge[++ecnt].v = v;
    edge[ecnt].w   = w;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
void add(int u, int v, int w) {
    _add(u, v, w);
    _add(v, u, 0);
}
int n, m, s, t;
int level[N];
int id(int x, int y) {
    return (x - 1) * m + y;
}
int ans, cnt;
bool bfs(int s, int t) {
    memset(level, 0, sizeof(level));
    memcpy(cur, head, sizeof(head));
    queue<int> q;
    q.push(s);
    level[s] = 1;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = head[x]; i; i = edge[i].nxt) {
            int v = edge[i].v;
            if (edge[i].w && level[v] == 0) {
                level[v] = level[x] + 1;
                q.push(v);
            }
        }
    }
    return level[t];
}
int dfs(int x, int t, int maxflow) {
    if (x == t) {
        return maxflow;
    }
    int res = 0;
    for (int &i = cur[x]; i && res < maxflow; i = edge[i].nxt) {
        int v = edge[i].v;
        if (edge[i].w && level[v] == level[x] + 1) {
            int x = dfs(v, t, min(edge[i].w, maxflow - res));
            if (x) {
                edge[i].w -= x;
                edge[i ^ 1].w += x;
                res += x;
            }
        }
    }
    if (res < maxflow) {
        level[x] = -1;
    }
    return res;
}
int dinic(int s, int t) {
    int res = 0;
    while (bfs(s, t)) {
        // cout << "P" << endl;
        int x;
        while (x = dfs(s, t, INF)) {
            res += x;
        }
    }
    return res;
}
int main() {
    cin >> n >> m;
    s   = 0;
    t   = N - 1;
    cnt = n * m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            ans += x;
            add(s, id(i, j), x);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            ans += x;
            add(id(i, j), t, x);
        }
    }
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            ans += x;
            add(s, ++cnt, x);
            add(cnt, id(i, j), INF);
            add(cnt, id(i + 1, j), INF);
        }
    }
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            ans += x;
            add(++cnt, t, x);
            add(id(i, j), cnt, INF);
            add(id(i + 1, j), cnt, INF);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m - 1; j++) {
            int x;
            cin >> x;
            ans += x;
            add(s, ++cnt, x);
            add(cnt, id(i, j), INF);
            add(cnt, id(i, j + 1), INF);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m - 1; j++) {
            int x;
            cin >> x;
            ans += x;
            add(++cnt, t, x);
            add(id(i, j), cnt, INF);
            add(id(i, j + 1), cnt, INF);
        }
    }
    cout << ans - dinic(s, t) << endl;
    return 0;
}
// Asusetic eru quionours
```

