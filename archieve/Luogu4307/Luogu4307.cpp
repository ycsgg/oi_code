#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 8005;
namespace NetworkFlow {
const int INF = 0x3f3f3f3f;
struct Graph {
    struct Node {
        int v, w, c, nxt;
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
    void add(int u, int v, int w, int c) {
        edge.emplace_back(Node{v, w, c, head[u]});
        head[u] = edge.size() - 1;
    }
    void add_flow(int u, int v, int w, int c) {
        add(u, v, w, c);
        add(v, u, 0, -c);
    }
};
int dis[N];
bool vis[N];
bool bfs(int S, int T, const Graph &G) {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[S] = 0;
    vis[S] = 1;
    std::queue<int> q;
    q.push(S);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = G.head[now]; ~i; i = G.edge[i].nxt) {
            int v      = G.edge[i].v;
            auto &edge = G.edge;
            if (edge[i].w && dis[edge[i].v] > dis[now] + edge[i].c) {
                dis[v] = dis[now] + edge[i].c;
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return dis[T] < INF;
}
vector<int> cur;
int cost;
int dfs(int x, int T, int maxflow, Graph &G) {
    vis[x] = 1;
    if (x == T) {
        cost += maxflow * dis[T];
        return maxflow;
    }
    int res = 0;
    for (int i = cur[x]; ~i && res < maxflow; i = G.edge[i].nxt) {
        cur[x] = i;
        int v  = G.edge[i].v;
        if (v != T && vis[v])
            continue;
        if (G.edge[i].w && dis[v] == dis[x] + G.edge[i].c) {
            int x = dfs(v, T, min(G.edge[i].w, maxflow - res), G);
            if (x) {
                G.edge[i].w -= x;
                G.edge[i ^ 1].w += x;
                res += x;
            }
            if (res == maxflow) {
                break;
            }
        }
    }
    return res;
}
pair<int, int> MCMF(const int &S, const int &T, const Graph &G) {
    cur.resize(G.head.size());
    Graph tmpG = G;
    int res    = 0;
    cost       = 0;
    while (bfs(S, T, tmpG)) {
        cur.assign(tmpG.head.begin(), tmpG.head.end());
        int x;
        while (x = dfs(S, T, INF, tmpG)) {
            res += x;
        }
    }
    return make_pair(res, cost);
}
} // namespace NetworkFlow
NetworkFlow::Graph G;
int n, m, s, t;
int a[N], b[N], c[N], d[N];
int in[N];
int main() {
    cin >> n >> m;
    int S = 0, T = n + m + 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
    }
    G.resize(n + m + 2);
    for (int i = 1; i <= m; i++) {
        G.add_flow(S, i, 1, 0);
        int x, y;
        cin >> x >> y;
        G.add_flow(i, x + m, 1, 0);
        G.add_flow(i, y + m, 1, 0);
        in[x]++;
        in[y]++;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        b[i] += in[i];
        ans += a[i] * a[i] * c[i] + b[i] * b[i] * d[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= in[i]; j++) {
            G.add_flow(i + m, T, 1,
                       2 * c[i] * a[i] + c[i] + d[i] - 2 * d[i] * b[i]);
            b[i]--;
            a[i]++;
        }
    }
    cout << NetworkFlow::MCMF(S, T, G).second + ans << endl;
}
F
    // Asusetic eru quionours
