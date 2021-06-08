### P4897 【模板】最小割树（Gomory-Hu Tree）

最小割树基于一个事实，一个图的最小割一定会把原图分成两个连通块

类比树形，删去一个边也会分成两个连通块，如果我们把最小割的边以一种方式映射到树边，就构成了一个性质很好的双射（比如证明最多有 $n-1$ 种最小割）

我们使树上的边断开后两个点集正好等于这个最小割的两个点集，就能保证双射

同时直接根据这个性质构造，随便选出两个点，跑一个最小割，然后连边，之后分治到两个点集里继续操作，容易验证这是对的

复杂度理论上 $O(n^3m)$ 实际上 网络流

```cpp
#include <cstring>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 505 * 2;
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
int lg[N];
namespace MinCutTree {
struct Graph {
    struct Node {
        int v, w;
    };
    vector<Node> edge[N];
    void _add(int u, int v, int w) {
        edge[u].emplace_back(Node{v, w});
    }
    void add(int u, int v, int w) {
        _add(u, v, w);
        _add(v, u, w);
    }
} Tr;
int id[N], tmp1[N], tmp2[N];
void _build(int l, int r) {
    if (l == r) {
        return;
    }
    int s = id[l], t = id[l + 1];
    int cut = NetworkFlow::MaxFlow(s, t, G);
    Tr.add(s, t, cut);
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
int dep[N], anc[N][12], st[N][12];
void predfs(int x, int fa) {
    dep[x] = dep[fa] + 1;
    for (int i = 1; i <= 11; i++) {
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
        st[x][i]  = min(st[x][i - 1], st[anc[x][i - 1]][i - 1]);
    }
    for (auto e : Tr.edge[x]) {
        int v = e.v;
        if (v == fa)
            continue;
        anc[v][0] = x;
        st[v][0]  = e.w;
        predfs(v, x);
    }
}
void build(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 11; j++) {
            st[i][j] = 0x3f3f3f3f;
        }
    }
    for (int i = 1; i <= n; i++) {
        id[i] = i;
    }
    _build(1, n);
    predfs(1, 0);
}
int query(int x, int y) {
    int ans = 0x7f7f7f7f;
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 11; i >= 0; i--) {
        if (dep[anc[x][i]] >= dep[y]) {
            ans = min(ans, st[x][i]);
            x   = anc[x][i];
        }
    }
    if (x == y) {
        return ans;
    }
    for (int i = 11; i >= 0; i--) {
        if (anc[x][i] != anc[y][i]) {
            ans = min(ans, st[x][i]);
            ans = min(ans, st[y][i]);
            x   = anc[x][i];
            y   = anc[y][i];
        }
    }
    ans = min(ans, st[x][0]);
    ans = min(ans, st[y][0]);
    return ans;
}
} // namespace MinCutTree

int n, m, q;
int main() {
    lg[1] = 0;
    for (int i = 2; i < N; i++) {
        lg[i] = lg[i >> 1] + 1;
    }
    cin >> n >> m;
    G.resize(n + 1);
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        G.add_flow(a, b, c);
        G.add_flow(b, a, c);
    }
    MinCutTree::build(n);
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << MinCutTree::query(u, v) << endl;
    }
    return 0;
}
// Asusetic eru quionours
```

