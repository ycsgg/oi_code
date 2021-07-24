### P5295 [北京省选集训2019]图的难题

一个图满足要求的充要条件所有子图满足 $|E|\le2|V|-2$ 证明待补充

所以仅需要判断是否存在有子图使得 $|E| > 2|V|-2$

考虑给边建点点权为 $1$ 点的点权为 $-2$ 跑一个最大权闭合子图就能找到 $|E|-2|V|$ 最大的子图

因为不能不选，可以枚举每个点钦定选

正经做法是加点退流，不过枚举可过

```cpp
#include <array>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 505 + 1005;
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
    if (res < maxflow) {
        level[x] = -1;
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
int MinCut(const int &S, const int &T, Graph &G) {
    return MaxFlow(S, T, G);
}
} // namespace NetworkFlow
int T;
using NetworkFlow::INF;
int main() {
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<int> u(m + 1), v(m + 1);
        int S = 0, T = n + m + 1;
        for (int i = 1; i <= m; i++) {
            cin >> u[i] >> v[i];
        }
        int ans = -100000;
        for (int i = 1; i <= n; i++) {
            ans = max(
                [&](int x) -> int {
                    NetworkFlow::Graph G(n + m + 2);
                    for (int i = 1; i <= m; i++) {
                        G.add_flow(S, i, 1);
                        G.add_flow(i, m + u[i], INF);
                        G.add_flow(i, m + v[i], INF);
                    }
                    for (int i = 1; i <= n; i++) {
                        if (x == i)
                            continue;
                        G.add_flow(i + m, T, 2);
                    }
                    return m - 2 - NetworkFlow::MinCut(S, T, G);
                }(i),
                ans);
        }
        if (ans > -2) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
        }
    }
    return 0;
}
// Asusetic eru quionours
```

