#include <array>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
namespace NetworkFlow {
const int INF = 0x3f3f3f3f;
struct Graph {
    struct Node {
        int v, w, nxt;
    };
    vector<Node> edge;
    vector<int> head;
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
        // meow("u:%d v:%d flow:%d\n", u, v, w);
        add(u, v, w);
        add(v, u, 0);
    }
};
int level[N];
bool bfs(int S, int T, const Graph &G) {
    memset(level, 0, sizeof(level));
    level[S] = 1;
    std::queue<int> q;
    q.push(S);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = G.head[now]; ~i; i = G.edge[i].nxt) {
            int v = G.edge[i].v;
            if (!level[v] && G.edge[i].w) {
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
        cur[x] = i;
        int v  = G.edge[i].v;
        if (G.edge[i].w && level[v] == level[x] + 1) {
            int x = dfs(v, T, std::min(G.edge[i].w, maxflow - res), G);
            if (x) {
                G.edge[i].w -= x;
                G.edge[i ^ 1].w += x;
                res += x;
            }
        }
    }
    /*if (res < maxflow) {
        level[x] = -1;
    }*/
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
int h[N], r[N], s[80][80];
int main() {
    int n, m, k;
    cin >> n >> m >> k;
    int S = 0, T = N - 2;
    n += 2;
    for (int i = 1; i <= m; i++) {
        cin >> h[i] >> r[i];
        for (int j = 0; j < r[i]; j++) {
            cin >> s[i][j];
            s[i][j] += 2;
        }
    }
    int t   = 1;
    int sum = 0;
    NetworkFlow::Graph G(N - 1);
    using NetworkFlow::INF;
    G.add_flow(S, 2, INF);
    G.add_flow(1, T, INF);
    while (t < 1000) {
        G.add_flow(S, n * t + 2, INF);
        G.add_flow(n * t + 1, T, INF);
        for (int i = 1; i <= n; i++) {
            G.add_flow(n * (t - 1) + i, n * t + i, INF);
        }
        for (int i = 1; i <= m; i++) {
            int x = s[i][(t - 1) % r[i]];
            int y = s[i][t % r[i]];
            G.add_flow(n * (t - 1) + x, n * t + y, h[i]);
        }
        sum += NetworkFlow::MaxFlow(S, T, G);
        if (sum >= k) {
            cout << t << endl;
            return 0;
        }
        ++t;
    }
    cout << 0 << endl;
    return 0;
    return 0;
}
// Asusetic eru quionours
