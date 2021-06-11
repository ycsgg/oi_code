#include <iostream>
#include <set>
#include <vector>
using namespace std;
const int N = 1e5 + 5;
struct Graph {
    struct Node {
        int v, w;
    };
    vector<Node> edge[N];
    void add(int u, int v, int w) {
        edge[u].emplace_back(Node{v, w});
    }
};
int cur[N];
int st[N * 4], top;
bool vis[N * 4 + 10];
int n, m, t;
void dfs(int x, const Graph &G1) {
    for (int &i = cur[x]; i < G1.edge[x].size(); i++) {
        auto &e = G1.edge[x][i];
        if (vis[abs(e.w)]) {
            continue;
        }
        vis[abs(e.w)] = 1;
        dfs(e.v, G1);
        st[++top] = e.w;
    }
}
Graph G;
int deg[N];
int in[N], out[N];
int fa[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) {
        return 0;
    }
    fa[x] = y;
    return 1;
}
bool used[N];
int cnt;
int main() {
    cin >> t;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    int tot = n;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G.add(u, v, i);
        used[u] = used[v] = 1;
        tot -= merge(u, v);
        if (t == 1) {
            G.add(v, u, -i);
            deg[u]++;
            deg[v]++;
        } else {
            in[v]++;
            out[u]++;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            cnt++;
        }
    }
    if (tot - cnt != 1 && tot != 1 && m != 0) {
        cout << "NO" << endl;
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        if (in[i] != out[i] || (deg[i] & 1)) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    for (int i = 1; i <= n; i++) {
        dfs(i, G);
        if (top == m)
            break;
    }
    for (int i = top; i >= 1; i--) {
        cout << st[i] << " ";
    }
    return 0;
}
// Asusetic eru quionours