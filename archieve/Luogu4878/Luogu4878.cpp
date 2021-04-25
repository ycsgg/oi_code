#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N   = 1005;
const int M   = 40005;
const int INF = 0x3f3f3f3f;
int n, ml, md;
struct Edge {
    int nxt, v, w;
} edge[M];
int head[N], tot;
inline void add(int x, int y, int v) {
    edge[++tot].nxt = head[x];
    edge[tot].v     = y;
    edge[tot].w     = v;
    head[x]         = tot;
}
queue<int> q;
int vis[N], dis[N], cnt[N];
void spfa(int s) {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    q.push(s);
    vis[s] = 1, dis[s] = 0;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = head[now]; i; i = edge[i].nxt) {
            int v = edge[i].v;
            if (dis[now] + edge[i].w < dis[v]) {
                dis[v] = dis[now] + edge[i].w;
                cnt[v] = cnt[now] + 1;
                if (cnt[v] >= n) {
                    cout << -1 << endl;
                    exit(0);
                }
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
}
int main() {
    cin >> n >> ml >> md;
    for (int i = 1; i <= n; i++) {
        add(0, i, 0);
    }
    for (int i = 1; i < n; i++) {
        add(i + 1, i, 0);
    }
    for (int i = 1; i <= ml; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
    }
    for (int i = 1; i <= md; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add(v, u, -w);
    }
    spfa(0);
    spfa(1);
    if (dis[n] == INF) {
        cout << "-2" << endl;
    } else {
        cout << dis[n] << endl;
    }
    return 0;
}
// Asusetic eru quionours
