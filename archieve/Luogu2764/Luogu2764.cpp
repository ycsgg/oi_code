#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 1508;

namespace NetworkFlow {
const int INF = 0x3f3f3f3f;
struct Graph {
    struct Node {
        int v, w, nxt;
    };
    vector<int> head;
    vector<Node> edge;
    Graph() {
    }
    Graph(int n) : head(n, -1) {
    }
    void resize(int n) {
        head.resize(n);
        head.assign(n, -1);
    }
    void add(int u, int v, int w) {
        edge.emplace_back(Node{v, w, head[u]});
        head[u] = edge.size() - 1;
    }
    void add_flow(int u, int v, int w) {
        // cout << u << " " << v << endl;
        add(u, v, w);
        add(v, u, 0);
    }
};
int level[N];
bool bfs(const int &S, const int &T, const Graph &G) {
    memset(level, 0, sizeof(level));
    level[S] = 1;
    queue<int> q;
    q.push(S);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = G.head[now]; ~i; i = G.edge[i].nxt) {
            auto &edge = G.edge;
            int v      = edge[i].v;
            if (!level[v] && edge[i].w) {
                level[v] = level[now] + 1;
                q.push(v);
            }
        }
    }
    return level[T];
}
vector<int> cur;
int dfs(int x, int T, int maxflow, Graph &G) {
    if (x == T) {
        return maxflow;
    }
    int res = 0;
    for (int i = cur[x]; ~i && res < maxflow; i = G.edge[i].nxt) {
        cur[x]     = i;
        auto &edge = G.edge;
        int v      = edge[i].v;
        if (G.edge[i].w && level[v] == level[x] + 1) {
            int x = dfs(v, T, min(edge[i].w, maxflow - res), G);
            if (x) {
                edge[i].w -= x;
                edge[i ^ 1].w += x;
                res += x;
            }
        }
    }
    return res;
}
int MaxFlow(const int S, const int T, Graph &G) {
    cur.resize(G.head.size());
    Graph &tmpG = G;
    int res     = 0;
    while (bfs(S, T, tmpG)) {
        cur.assign(tmpG.head.begin(), tmpG.head.end());
        int x;
        while (x = dfs(S, T, INF, tmpG)) {
            res += x;
        }
    }
    return res;
}
} // namespace NetworkFlow
namespace DSU {
int fa[N];
void init(int n) {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
}
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        fa[x] = y;
    }
}
} // namespace DSU

int main() {
    int n, m;
    cin >> n >> m;
    int S = 0, T = n * 2 + 1;
    NetworkFlow::Graph G(T + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G.add_flow(u, v + n, 1);
    }
    for (int i = 1; i <= n; i++) {
        G.add_flow(S, i, 1);
        G.add_flow(i + n, T, 1);
    }
    int ans = n - NetworkFlow::MaxFlow(S, T, G);
    DSU::init(n);
    for (int x = 1; x <= n; x++) {
        for (int i = G.head[x]; ~i; i = G.edge[i].nxt) {
            if (!G.edge[i].w && G.edge[i].v != S && G.edge[i].v != T) {
                DSU::merge(x, G.edge[i].v - n);
                // cout << i << " " << G.edge[i].v - n << endl;
            }
        }
    }
    for (int i = n; i >= 1; i--) {
        bool flag = 0;
        for (int j = 1; j <= n; j++) {
            if (i == DSU::find(j)) {
                cout << j << " ";
                flag = 1;
            }
        }
        if (flag) {
            cout << endl;
        }
    }
    cout << ans << endl;
}
// Asusetic eru quionours