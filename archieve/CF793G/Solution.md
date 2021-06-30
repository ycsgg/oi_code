### CF793G Oleg and chess

比较套路

考虑如果没有矩阵的限制就是每行每列互相连边跑最大匹配，禁止的点不能连边，但是 $n^2$ 的边数没法跑

观察连边可以发现绝大部分边都是一个点连向某一个区间，那就线段树优化建图

具体的可以用扫描线的思路，把矩阵左边界的 $(y_1,y_2)$ 置为不能选，右边界再去掉限制，新建点向这一列内连边即可

注意需要先加后删

边数为 $n\log n$ 级别，网络流跑不满所以能过

```cpp
#include <array>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N   = 1e4 + 5;
const int INF = 0x7f7f7f7f;
struct Graph {
    struct Node {
        int v, w, nxt;
    };
    std::vector<int> head;
    std::vector<Node> edge;
    Graph() {
    }
    Graph(int n) : head(n + 1, -1){};
    void resize(int n) {
        head.assign(n + 1, -1);
    }
    void add(int u, int v, int w) {
        if (head.size() < u) {
            head.reserve(u * 2);
        }
        edge.emplace_back(Node{v, w, head[u]});
        head[u] = edge.size() - 1;
    }

    void add_flow(int u, int v, int w) {
        add(u, v, w);
        add(v, u, 0);
    }
};
namespace NetworkFlow {
std::vector<int> level;
bool bfs(int S, int T, const Graph &G) {
    level.assign(G.head.size(), 0);
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
std::vector<int> cur;
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
    level.resize(G.head.size());
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
int S, T;
Graph G;
array<int, N * 20> id, col;
int idcnt;
namespace SegmentTree {
using namespace NetworkFlow;
#define ls(x) (x * 2)
#define rs(x) (x * 2 + 1)
void build(int rt, int l, int r) {
    if (l == r) {
        id[rt] = l;
        G.add_flow(l, T, 1);
        col[rt] = l;
        return;
    }
    id[rt] = col[rt] = ++idcnt;
    int mid          = (l + r) / 2;
    build(ls(rt), l, mid);
    build(rs(rt), mid + 1, r);
    G.add_flow(col[rt], col[ls(rt)], INF);
    G.add_flow(col[rt], col[rs(rt)], INF);
}
void update(int rt, int l, int r, int L, int R, int v) {
    if (L <= l && r <= R) {
        if (v) {
            id[rt] = col[rt];
        } else {
            id[rt] = -1;
        }
        return;
    }
    int mid = (l + r) / 2;
    id[rt]  = ++idcnt;
    if (L <= mid) {
        update(ls(rt), l, mid, L, R, v);
    }
    if (mid < R) {
        update(rs(rt), mid + 1, r, L, R, v);
    }
    if (id[ls(rt)] != -1) {
        G.add_flow(id[rt], id[ls(rt)], INF);
    }
    if (id[rs(rt)] != -1) {
        G.add_flow(id[rt], id[rs(rt)], INF);
    }
}
#undef ls
#undef rs
} // namespace SegmentTree
int n, q;
vector<pair<int, int>> st[N], ed[N];
int main() {
    cin >> n >> q;
    G.resize(n * 80);
    S = idcnt = n + 1;
    T         = S + 1;
    for (int i = 1; i <= q; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        st[x1].emplace_back(make_pair(y1, y2));
        ed[x2 + 1].emplace_back(make_pair(y1, y2));
    }
    SegmentTree::build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        for (auto v : ed[i]) {
            SegmentTree::update(1, 1, n, v.first, v.second, 1);
        }
        for (auto v : st[i]) {
            SegmentTree::update(1, 1, n, v.first, v.second, 0);
        }
        if (id[1] != -1)
            G.add_flow(S, id[1], 1);
    }
    cout << NetworkFlow::MaxFlow(S, T, G);
    return 0;
}
// Asusetic eru quionours
```

#线段树优化建图
#网络流