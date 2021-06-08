#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;
const int N = 855 * 2;
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
    if (res < maxflow) {
        level[x] = -1;
    }
    return res;
}
int MaxFlow(const int S, const int T, const Graph &G) {
    cur.resize(G.head.size());
    Graph tmpG = G;
    int res    = 0;
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
NetworkFlow::Graph G;
namespace MinCutTree {
int id[N], tmp1[N], tmp2[N];
set<int> val;
void _build(int l, int r) {
    if (l == r) {
        return;
    }
    int s = id[l], t = id[l + 1];
    int cut = NetworkFlow::MaxFlow(s, t, G);
    // TG
    val.insert(cut);
    int cnt1 = 0, cnt2 = 0;
    for (int i = l; i <= r; i++) {
        if (NetworkFlow::level[id[i]]) {
            tmp1[++cnt1] = id[i];
        } else {
            tmp2[++cnt2] = id[i];
        }
    }
    for (int i = l; i <= l + cnt1 - 1; i++) {
        id[i] = tmp1[i - l + 1];
    }
    for (int i = l + cnt1; i <= r; i++) {
        id[i] = tmp2[i - cnt1 - l + 1];
    }
    _build(l, l + cnt1 - 1);
    _build(l + cnt1, r);
}
int solve(int n) {
    for (int i = 1; i <= n; i++) {
        id[i] = i;
    }
    _build(1, n);
    return val.size();
}
} // namespace MinCutTree

int n, m, q;
int main() {
    cin >> n >> m;
    G.resize(n + 1);
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        G.add_flow(a, b, c);
        G.add_flow(b, a, c);
    }
    cout << MinCutTree::solve(n);
    return 0;
}
// Asusetic eru quionours.