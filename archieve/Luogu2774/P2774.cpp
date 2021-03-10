#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int INF  = 0x3f3f3f3f;
const int NINF = -0x3f3f3f3f;
int n, m, s, t;
const int N    = 80080;
const int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
struct Edge {
    int v;
    int w, nxt;
} edge[N];
int head[N], ecnt = 1, cur[N];
int level[N];
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
int id(int x, int y) {
    return m * (x - 1) + y;
}
bool bfs(int s, int t) {
    memset(level, -1, sizeof(level));
    level[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = head[x]; i; i = edge[i].nxt) {
            if (edge[i].w && level[edge[i].v] == -1) {
                level[edge[i].v] = level[x] + 1;
                q.push(edge[i].v);
            }
        }
    }
    return (level[t] != -1);
}
int dfs(int x, int flow) {
    if (x == t || flow == 0) {
        return flow;
    }
    int used = 0;
    for (int &i = cur[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (level[v] == level[x] + 1) {
            int _f = dfs(v, min(flow - used, edge[i].w));
            if (_f) {
                used += _f;
                edge[i].w -= _f;
                edge[i ^ 1].w += _f;
            }
        }
    }
    return used;
}
long long dinic() {
    long long res = 0;
    while (bfs(s, t)) {
        memcpy(cur, head, sizeof(cur));
        res += dfs(s, 1e9);
    }
    return res;
}
long long sum;
int main() {
    cin >> n >> m;
    s = 0, t = n * m + 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int a;
            cin >> a;
            sum += a;
            if ((i + j) % 2) {
                add(s, id(i, j), a);
            } else {
                add(id(i, j), t, a);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if ((i + j) % 2) {
                for (int k = 0; k < 4; k++) {
                    int nx = i + dx[k], ny = j + dy[k];
                    if (nx > n || ny > m || nx < 1 || ny < 1)
                        continue;
                    add(id(i, j), id(nx, ny), 1e8);
                }
            }
        }
    }
    cout << sum - dinic();
    return 0;
}