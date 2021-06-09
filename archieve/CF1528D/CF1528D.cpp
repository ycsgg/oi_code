#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long int_;
const int N   = 605;
const int INF = (1 << 30) - 1;
struct Graph {
    struct Node {
        int v, w;
    };
    vector<Node> edge[N];
    void add(int u, int v, int w) {
        edge[u].emplace_back(Node{v, w});
    }
    vector<Node> &operator[](const int x) {
        return edge[x];
    }

} G;

int dis[N], n, m;
bool vis[N];
void dijkstra(int S) {
    fill(dis, dis + n, INF);
    memset(vis, 0, n);
    for (auto y : G[S]) {
        int v  = y.v;
        int w  = y.w;
        dis[v] = min(dis[v], w);
    }
    for (int i = 1; i <= n; ++i) {
        int id = -1;
        for (int j = 0; j < n; j++) {
            if (!vis[j]) {
                if ((id == -1) || (dis[id] > dis[j])) {
                    id = j;
                }
            }
        }
        if (dis[id] == INF)
            break;
        vis[id]           = 1;
        dis[(id + 1) % n] = min(dis[(id + 1) % n], dis[id] + 1);
        for (auto e : G[id]) {
            int v  = (e.v + dis[id]) % n;
            dis[v] = min(dis[v], dis[id] + e.w);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        G.add(u, v, w);
    }
    for (int i = 0; i < n; ++i) {
        dijkstra(i);
        for (int j = 0; j < n; j++) {
            if (i == j) {
                cout << 0 << " ";
                continue;
            }
            cout << dis[j] << " ";
        }
        cout << endl;
    }
    return 0;
}
// Asusetic eru quinours.