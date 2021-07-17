#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N      = 108;
const double eps = 1e-6;
bool Eq0(double x) {
    return (x < eps && x > -eps);
}
namespace NetworkFlow {
const int INF = 0x3f3f3f3f;

struct Graph {
    struct Node {
        int v, nxt;
        double w;
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
    void add(int u, int v, double w) {
        edge.emplace_back(Node{v, head[u], w});
        head[u] = edge.size() - 1;
    }
    void add_flow(int u, int v, double w) {
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
            if (!level[v] && !Eq0(G.edge[i].w)) {
                level[v] = level[now] + 1;
                q.push(v);
            }
        }
    }
    return level[T];
}
vector<int> cur;
double dfs(int x, int T, double maxflow, Graph &G) {
    if (x == T) {
        return maxflow;
    }
    double res = 0;
    for (int i = cur[x]; ~i && res < maxflow; i = G.edge[i].nxt) {
        cur[x] = i;
        int v  = G.edge[i].v;
        if (!Eq0(G.edge[i].w) && level[v] == level[x] + 1) {
            double x = dfs(v, T, min(G.edge[i].w, maxflow - res), G);
            if (!Eq0(x)) {
                G.edge[i].w -= x;
                G.edge[i ^ 1].w += x;
                res += x;
            }
        }
    }
    if (res < maxflow) {
        level[x] = -1;
    }
    return res;
}
double MaxFlow(const int S, const int T, const Graph &G) {
    cur.resize(G.head.size());
    Graph tmpG = G;
    double res = 0;
    while (bfs(S, T, tmpG)) {
        cur.assign(tmpG.head.begin(), tmpG.head.end());
        double x;
        while (x = dfs(S, T, INF, tmpG)) {
            res += x;
        }
    }
    return res;
}
} // namespace NetworkFlow
NetworkFlow::Graph G;
double ans;
int n, m, p;
int S = 1, T;
bool check(double x) {
    auto G1 = G;
    for (auto &e : G1.edge) {
        e.w = min(e.w, x);
    }
    return Eq0(NetworkFlow::MaxFlow(S, T, G1) - ans);
}
int main() {
    cin >> n >> m >> p;
    double l = 0, r = 0;
    G.resize(n + 2);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        r = max(r, (double)w);
        cin >> u >> v >> w;
        G.add_flow(u, v, w);
    }
    S   = 1;
    T   = n;
    ans = NetworkFlow::MaxFlow(S, T, G);
    printf("%.0lf\n", ans);
    while (r - l > eps) {
        double mid = (l + r) / 2.0;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    printf("%.4lf", r * p);
}
// Asusetic eru quionours
