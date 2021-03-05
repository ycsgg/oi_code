### P3705 [SDOI2017]新生舞会

分数规划套个方格取数

最大化$V=\frac{\sum a_i}{\sum b_i}$，每行每列仅能选一个

二分$V$，写成$\sum a_i-V*b_i=0$

连边从男向女连一个容量为$1$，费用为$a_{i,j}-V*b_{i,j}$的边，最大费用最大流如果能大于$0$，就存在一种分配方案

```cpp
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const double eps = 1e-9;
const int N      = 205;
const int INF    = 0x3f3f3f3f;
const int NINF   = -0x3f3f3f3f;
struct Edge {
    int v;
    double c;
    int w, nxt;
} edge[N * N * 2];
int head[N * N * 2], ecnt = 1;
int cur[N * N * 2];
int level[N * N * 2];
double dis[N * N * 2];
bool vis[N * N * 2];
void _add(int u, int v, int w, double c) {
    edge[++ecnt].v = v;
    edge[ecnt].w   = w;
    edge[ecnt].c   = c;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
bool bfs(int s, int t) {
    memset(vis, 0, sizeof(vis));
    for (int i = s; i <= t; i++) {
        dis[i] = NINF;
    }
    dis[s] = 0;
    vis[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = 0;
        for (int i = head[x]; i; i = edge[i].nxt) {
            int v = edge[i].v;
            if (dis[v] < dis[x] + edge[i].c && edge[i].w) {
                dis[v] = dis[x] + edge[i].c;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
    return dis[t] != NINF;
}
double res = 0;
void add(int u, int v, int w, double c) {
    _add(u, v, w, c);
    _add(v, u, 0, -c);
}
int dfs(int x, int t, int maxflow) {
    vis[x] = 1;
    if (x == t) {
        return maxflow;
    }
    int used = 0;
    for (int &i = cur[x]; i; i = edge[i].nxt) {
        if (!vis[edge[i].v] && edge[i].w &&
            (dis[x] + edge[i].c == dis[edge[i].v])) {
            int flow = dfs(edge[i].v, t, min(edge[i].w, maxflow - used));
            if (flow) {
                edge[i].w -= flow;
                edge[i ^ 1].w += flow;
                res += 1.0 * edge[i].c * flow;
                used += flow;
            }
            if (used == maxflow)
                return used;
        }
    }
    return used;
}
int n;
int s, t;
int a[N][N], b[N][N];
void dinic(int s, int t) {
    res = 0;
    while (bfs(s, t)) {
        memcpy(cur, head, sizeof(head));
        vis[t] = 1;
        while (vis[t]) {
            memset(vis, 0, sizeof(vis));
            dfs(s, t, INF);
        }
    }
}
bool check(double C) {
    s = 0, t = 2 * n + 1;
    memset(head, 0, sizeof(head));
    ecnt = 1;
    for (int i = 1; i <= n; i++) {
        add(s, i, 1, 0);
        add(i + n, t, 1, 0);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            add(i, j + n, 1, 1.0 * a[i][j] - C * b[i][j]);
        }
    }
    dinic(s,t);
    return (res >= 0);
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> b[i][j];
        }
    }
    double l = 0, r = 1e5 + 3, ans;
    while ((r - l) > eps) {
        double mid = 1.0 * (l + r) / 2.0;
        if (check(mid)) {
            l   = mid + eps;
            ans = mid;
        } else {
            r = mid - eps;
        }
    }
    printf("%.6lf", ans);
    return 0;
}
```