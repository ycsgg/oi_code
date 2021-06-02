### P3191 [HNOI2007]紧急疏散EVACUATE

二分答案+网络流

先二分答案 $x$

源点向每个空地连容量为 $1$ 的边代表一个人

把门拆成 $x$ 个点表示 $[1,x]$ 每个时间点的门并且每个门向汇点连容量为 $1$ 的边，表示每秒过一个人

因为可能有多个人同一个时间到一个门，所以每个门向下一个时间的门连 $\infty$ 的边表示在时间上转移

空地到门连他到门时间的边即可，容量 $1$

最大流就是跑出去的人数

```cpp
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N    = 25;
const int M    = 1.4e6+7;
const int INF  = 0x7f7f7f7f;
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
struct Edge {
    int v;
    int w, nxt;
} edge[M];
int head[M], ecnt;
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
int n, m;
namespace Dinic {
int level[M];
int cur[M];
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
} // namespace Dinic

char mp[N][N];
bool vis[N][N];
int dis[N * N][N][N];
int Dcnt, pcnt;
bool checkbound(int x, int y) {
    return (x >= 1 && x <= n && y >= 1 && y <= m);
}
void bfs(int s, int sx, int sy) {
    memset(vis, 0, sizeof(vis));
    vis[sx][sy]    = 1;
    dis[s][sx][sy] = 0;
    queue<pair<int, int>> q;
    q.push(make_pair(sx, sy));
    while (!q.empty()) {
        pair<int, int> now = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = now.first + dx[i], ny = now.second + dy[i];
            if (checkbound(nx, ny) && !vis[nx][ny] && mp[nx][ny] == '.') {
                dis[s][nx][ny] = dis[s][now.first][now.second] + 1;
                q.push(make_pair(nx, ny));
                vis[nx][ny] = 1;
            }
        }
    }
}
int id[N][N];
bool check(int x) {
    int s = 0, t = M - 1;
    memset(head, 0, sizeof(head));
    ecnt = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mp[i][j] == '.') {
                add(s, id[i][j], 1);
            }
        }
    }
    for (int p = 1; p <= Dcnt; p++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (mp[i][j] == '.' && dis[p][i][j] <= x) {
                    add(id[i][j], (p - 1) * x + pcnt + dis[p][i][j], 1);
                }
            }
        }
    }
    for (int i = 1; i <= Dcnt; i++) {
        for (int j = 1; j <= x; j++) {
            int u = (i - 1) * x + pcnt;
            add(u + j, t, 1);
            if (j != x)
                add(u + j, u + j + 1, INF);
        }
    }
    // cout << Dinic::dinic(s, t) << endl;
    return (Dinic::dinic(s, t) == pcnt);
}
int main() {
    memset(dis, 0x3f, sizeof(dis));
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> mp[i] + 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mp[i][j] == 'D') {
                bfs(++Dcnt, i, j);
            }
            if (mp[i][j] == '.') {
                id[i][j] = ++pcnt;
            }
        }
    }
    int l = 1, r = 1005, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            r   = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }
    if (ans == -1) {
        cout << "impossible";
        return 0;
    }
    cout << ans;
    return 0;
}
// Asusetic eru quionours
```

