#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N   = 5005;
const int inf = 0x7f7f7f7f;
int T, cnt[N], dis[N], n, m;
bool vis[N];
struct Edge {
    int v;
    int w, nxt;
} edge[N * 2];
int head[N * 2], ecnt;
void add(int u, int v, int w) {
    edge[++ecnt].v = v;
    edge[ecnt].w   = w;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}

bool spfa(int s) {
    queue<int> q;
    memset(dis, -0x3f, sizeof(dis));
    q.push(s);
    dis[s] = 0;
    vis[s] = 1;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = 0;
        cnt[x]++;
        if (cnt[x] == n)
            return 0;
        for (int i = head[x]; i; i = edge[i].nxt) {
            int v = edge[i].v;
            if (dis[v] < dis[x] + edge[i].w) {
                dis[v] = dis[x] + edge[i].w;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
    return 1;
}

int main() {
    cin >> T;
    while (T--) {
        cin >> n >> m;
        ecnt = 0;
        memset(vis, 0, sizeof(vis));
        memset(head, 0, sizeof(head));
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            add(u - 1, v, w);
            add(v, u - 1, -w);
        }
        bool flag = 0;
        for (int i = 0; i <= n; i++) {
            if (!cnt[i]) {
                if (!spfa(i)) {
                    flag = 1;
                    break;
                }
            }
        }
        if (!flag) {
            cout << "true" << endl;
        } else {
            cout << "false" << endl;
        }
    }
    return 0;
}
// Asusetic eru quionours