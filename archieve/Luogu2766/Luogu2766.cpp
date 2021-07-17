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
int n;
int a[N];
int dp[N];
NetworkFlow::Graph G;
int main() {
    cin >> n;
    int S = 0, T = n * 2 + 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        dp[i] = 1;
    }
    if (n == 1) {
        cout << 1 << endl << 1 << endl << 1;
        return 0;
    }
    G.resize(n * 2 + 2);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (a[j] <= a[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    for (int i = 2; i < n; i++) {
        if (dp[i] == 1) {
            G.add_flow(S, i, 1);
        }
        if (dp[i] == ans) {
            G.add_flow(i + n, T, 1);
        }
        G.add_flow(i, i + n, 1);
        for (int j = 1; j < i; j++) {
            if (a[j] <= a[i] && dp[i] == dp[j] + 1) {
                G.add_flow(j + n, i, 1);
            }
        }
    }
    for (int j = 1; j < n; j++) {
        if (a[j] <= a[n] && dp[n] == dp[j] + 1) {
            G.add_flow(j + n, n, 1);
        }
    }
    NetworkFlow::Graph tmpG = G;
    tmpG.add_flow(1, 1 + n, 1);
    tmpG.add_flow(S, 1, 1);
    tmpG.add_flow(n, n + n, 1);
    if (dp[1] == ans) {
        tmpG.add_flow(1 + n, T, 1);
    }
    if (dp[n] == 1) {
        tmpG.add_flow(S, n, 1);
    }
    if (dp[n] == ans) {
        tmpG.add_flow(n + n, T, 1);
    }
    cout << NetworkFlow::MaxFlow(S, T, tmpG) << endl;
    G.add_flow(1, 1 + n, 0x3f3f3f3f);
    G.add_flow(S, 1, 0x3f3f3f3f);
    if (dp[1] == ans) {
        tmpG.add_flow(1 + n, T, 0x3f3f3f3f);
    }
    if (dp[n] == 1) {
        G.add_flow(S, n, 0x3f3f3f3f);
    }
    if (dp[n] == ans) {
        G.add_flow(n, n + n, 0x3f3f3f3f);
        G.add_flow(n + n, T, 0x3f3f3f3f);
    }
    int res = NetworkFlow::MaxFlow(S, T, G);
    cout << (res >= 0x3f3f3f3f ? n : res) << endl;
}
//Asusetic eru quionours
