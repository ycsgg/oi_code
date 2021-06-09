#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 300005;
bool vis[N];
queue<int> q;
int n, m;
struct Graph {
    struct Node {
        int v, w;
    };
    vector<Node> edge[N];
    void add(int u, int v, int w) {
        edge[u].emplace_back(Node{v, w});
    }
} G;
int tot[N], dis[N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, opt;
        cin >> opt >> u >> v;
        if (opt == 1) {
            G.add(u, v, 0);
            G.add(v, u, 0);
        } else if (opt == 2) {
            if (u == v) {
                cout << -1 << endl;
                return 0;
            }
            G.add(u, v, 1);
        } else if (opt == 3) {
            G.add(v, u, 0);
        } else if (opt == 4) {
            if (u == v) {
                cout << -1 << endl;
                return 0;
            }
            G.add(v, u, 1);
        } else if (opt == 5) {
            G.add(u, v, 0);
        }
    }
    for (int i = 1; i <= n; i++) {
        G.add(0, i, 1);
    }
    vis[0] = 1;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        if (tot[u] == n + 1) {
            cout << -1;
            return 0;
        }
        tot[u]++;
        for (auto e : G.edge[u]) {
            int v = e.v;
            if (dis[v] < dis[u] + e.w) {
                dis[v] = dis[u] + e.w;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        ans += 1ll * dis[i];
    cout << ans;
    return 0;
}
// Asusetic eru quionours.