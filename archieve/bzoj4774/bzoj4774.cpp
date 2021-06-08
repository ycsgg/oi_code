#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 1e4 + 5;
int n, m, d;
struct Graph {
    struct Node {
        int v, w;
    };
    vector<Node> edge[N];
    void add(int u, int v, int w) {
        edge[u].emplace_back(Node{v, w});
    }
} G;
int f[(1 << 8) + 5][N], g[(1 << 8) + 5];
bool vis[N];
int main() {
    cin >> n >> m >> d;
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        G.add(a, b, c);
        G.add(b, a, c);
    }
    int U = (1 << (d << 1)) - 1;
    memset(f, 0x3f, sizeof(f));
    memset(g, 0x3f, sizeof(g));
    for (int i = 1; i <= d; i++) {
        f[(1 << (i - 1))][i] = f[1 << (d + i - 1)][n - i + 1] = 0;
    }
    queue<int> q;
    for (int s = 0; s <= U; s++) {
        for (int i = 1; i <= n; i++) {
            for (int t = s & (s - 1); t; t = (t - 1) & s) {
                f[s][i] = min(f[s][i], f[t][i] + f[s ^ t][i]);
            }
            if (f[s][i] < 0x3f3f3f3f) {
                q.push(i);
                vis[i] = 1;
            }
        }
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            vis[x] = 0;
            for (auto e : G.edge[x]) {
                if (f[s][e.v] > f[s][x] + e.w) {
                    f[s][e.v] = f[s][x] + e.w;
                    if (!vis[e.v]) {
                        q.push(e.v);
                        vis[e.v] = 1;
                    }
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            g[s] = min(g[s], f[s][i]);
        }
    }
    auto ok = [&](const int x) -> bool {
        return (x & ((1 << d) - 1)) == (x >> d);
    };
    for (int s = 0; s <= U; s++) {
        for (int t = (s - 1) & s; t; t = (t - 1) & s) {
            if (ok(t) && ok(s ^ t)) {
                g[s] = min(g[s], g[t] + g[s ^ t]);
            }
        }
    }
    if (g[U] >= 0x3f3f3f3f) {
        cout << -1 << endl;
    } else {
        cout << g[U];
    }
    return 0;
}
// Asusetic eru quionours