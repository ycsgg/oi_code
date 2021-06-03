### P3163 [CQOI2014]危桥

从源点向 $a_1,b_1$ 连 $2a_n,2b_n$

汇点同样，但是问题是有可能 $b_2$ 的流量是来自 $a_1$ 而非 $b_1$

解决方案是把 $b_1$ $b_2$ 交换然后连边然后再跑一次，如果仍然满流就是真的满了

证明复杂，感性理解

```cpp
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 55;
struct Graph {
    struct Node {
        int v, w, nxt;
    };
    vector<int> head;
    vector<Node> edge;
    Graph() {
    }
    Graph(int n) : head(n, -1){};
    void resize(int n) {
        head.assign(n, -1);
    }
    void _add(int u, int v, int w) {
        edge.emplace_back(Node{v, w, head[u]});
        head[u] = edge.size() - 1;
    }
    void add(int u, int v, int w) {
        _add(u, v, w);
        _add(v, u, 0);
    }
} G1;

int n, a1, a2, an, b1, b2, bn;
char mp[N][N];
const int Inf = 0x3f3f3f3f;
namespace MaxFlow {
vector<int> cur;
vector<int> level;
bool bfs(int S, int T, const Graph &G) {
    level.assign(G.head.size() + 1, 0);
    level[S] = 1;
    queue<int> q;
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
int dfs(int x, int T, int maxflow, Graph &G) {
    if (x == T) {
        return maxflow;
    }
    int res = 0;
    for (int &i = cur[x]; ~i && res < maxflow; i = G.edge[i].nxt) {
        int v = G.edge[i].v;
        if (G.edge[i].w && level[v] == level[x] + 1) {
            int x = dfs(v, T, min(G.edge[i].w, maxflow - res), G);
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
int MaxFlow(int S, int T, Graph &G) {
    int res = 0;
    while (bfs(S, T, G)) {
        cur.assign(G.head.begin(), G.head.end());
        int x;
        while (x = dfs(S, T, Inf, G)) {
            res += x;
        }
    }
    return res;
}
} // namespace MaxFlow
int main() {
    while (cin >> n >> a1 >> a2 >> an >> b1 >> b2 >> bn) {
        G1.resize(n + 5);
        ++a1;
        ++a2;
        ++b1;
        ++b2;
        an *= 2;
        bn *= 2;
        int s = 0, t = n + 1;
        for (int i = 1; i <= n; i++) {
            cin >> mp[i] + 1;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (mp[i][j] == 'O') {
                    G1.add(i, j, 2);
                }
                if (mp[i][j] == 'N') {
                    G1.add(i, j, Inf);
                }
            }
        }
        G1.add(s, a1, an);
        G1.add(a2, t, an);
        Graph G = G1;
        G.add(s, b1, bn);
        G.add(b2, t, bn);
        if (!(MaxFlow::MaxFlow(s, t, G) == an + bn)) {
            cout << "No" << endl;
            continue;
        }
        G = G1;
        G.add(s, b2, bn);
        G.add(b1, t, bn);
        if (!(MaxFlow::MaxFlow(s, t, G) == an + bn)) {
            cout << "No" << endl;
            continue;
        }
        cout << "Yes" << endl;
    }
    return 0;
}
// Asusetic eru quionours
```

