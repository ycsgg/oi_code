#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 105;
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
int MinCut(const int &S, const int &T, Graph &G) {
    return MaxFlow(S, T, G);
}
} // namespace NetworkFlow
int n, m;
int main() {
    cin >> m >> n;
    NetworkFlow::Graph G(n + m + 2);
    int S   = 0;
    int T   = n + m + 1;
    int sum = 0;
    for (int i = 1; i <= m; i++) {
        int w;
        cin >> w;
        sum += w;
        G.add_flow(S, i, w);
        while (1) {
            int x;
            char c;
            scanf("%d%c", &x, &c);
            G.add_flow(i, x + m, NetworkFlow::INF);
            if (c == '\n' || c == '\r')
                break;
        }
    }
    for (int i = 1; i <= n; i++) {
        int w;
        cin >> w;
        G.add_flow(i + m, T, w);
    }
    int ans = sum - NetworkFlow::MinCut(S, T, G);
    for (int i = 1; i <= m; i++) {
        if (NetworkFlow::level[i] != 0) {
            cout << i << " ";
        }
    }
    puts("");
    for (int i = 1; i <= n; i++) {
        if (NetworkFlow::level[i + m] != 0) {
            cout << i << " ";
        }
    }
    puts("");
    cout << ans;
}
// Asusetic eru quionours.