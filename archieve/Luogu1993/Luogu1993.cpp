#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 1e4 + 5;
int n, m, dis[N], num[N];
bool vis[N];
struct Graph {
    struct Node {
        int v, w;
    };
    vector<Node> edge[N];
    void add(int u, int v, int w) {
        edge[u].emplace_back(Node{v, w});
    }
} G;
queue<int> q;
bool spfa(int x) {
    memset(dis, 0x3f, sizeof(dis));
    dis[x] = 0;
    q.push(x);
    vis[x] = true;
    num[x]++;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (auto e : G.edge[u]) {
            int v = e.v;
            if (dis[v] > dis[u] + e.w) {
                dis[v] = dis[u] + e.w;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = 1;
                    num[v]++;
                    if (num[v] == n + 1) {
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
        int opt, a, b, c;
        cin >> opt >> a >> b;
        if (opt == 1) {
            cin >> c;
            G.add(a, b, -c);
        } else if (opt == 2) {
            cin >> c;
            G.add(b, a, c);
        } else {
            G.add(a, b, 0);
            G.add(b, a, 0);
        }
    }
    for (int i = 1; i <= n; i++) {
        G.add(n + 1, i, 0);
    }
    if (!spfa(n + 1)) {
        cout << "No" << endl;
        return 0;
    }
    cout << "Yes" << endl;
    return 0;
}
// Asusetic eru quionours.