#include <iostream>
#include <queue>
using namespace std;
const int N = 1505, M = 5e4 + 10;
struct Edge {
    int v;
    long long w;
    int nxt;
} edge[M];
int head[N], ecnt;
void add(int u, int v, int w) {
    edge[++ecnt].v = v;
    edge[ecnt].w   = w;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
int n, m;
int tot[N];
long long dis[N];
bool vis[N];
queue<int> q;
int spfa(int S) {
    for (int i = 1; i <= n; i++) {
        dis[i] = -2e9;
    }
    dis[S] = 0;
    vis[S] = 1;
    q.push(S);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = head[u]; i; i = edge[i].nxt) {
            int v = edge[i].v;
            if (dis[v] < dis[u] + edge[i].w) {
                dis[v] = dis[u] + edge[i].w;
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                    ++tot[v];
                    if (tot[v] == n + 1) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
    }
    spfa(1);
    if(dis[n]==-2e9){
        cout << -1 << endl;
    }else{
        cout << dis[n];
    }
    return 0;
}