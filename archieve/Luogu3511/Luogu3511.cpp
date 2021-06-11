#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 2005;
struct Data {
    int u, v, w1, w2;
} e[N];
int n, m;
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
    void clear() {
        head.assign(n + 5, -1);
        edge.clear();
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
} // namespace NetworkFlow
NetworkFlow::Graph G;
vector<int> deg;
int id[N];
int fa[N];
int find(int x) {
    return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);
}
int merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        fa[x] = y;
        return -1;
    } else {
        return 0;
    }
}
bool used[N];
int up;
bool check(int x) {
    // cout << x << endl;
    G.clear();
    deg.assign(n + 5, 0);
    int S = 0, T = n + 1;
    int tot = 0;
    int siz = n;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    memset(used, 0, sizeof(used));
    for (int i = 1; i <= m; i++) {
        if (e[i].w1 <= x) {
            deg[e[i].u]--;
            deg[e[i].v]++;
            used[e[i].u] = used[e[i].v] = 1;
            siz += merge(e[i].u, e[i].v);
        }
        if (e[i].w2 <= x) {
            // cout << e[i].u << endl;
            id[i] = G.edge.size();
            G.add_flow(e[i].v, e[i].u, 1);
            used[e[i].u] = used[e[i].v] = 1;
            siz += merge(e[i].u, e[i].v);
        }
    }
    if (siz != 1 && siz - up != 1) {
        return 0;
    }
    // cout << "P" << endl;
    for (int i = 1; i <= n; i++) {
        if (deg[i] & 1) {
            return 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (deg[i] > 0) {
            tot += deg[i] / 2;
            G.add_flow(S, i, deg[i] / 2);
        } else {
            G.add_flow(i, T, -deg[i] / 2);
        }
    }
    return (NetworkFlow::MaxFlow(S, T, G) == tot);
}
int st[N], top;
bool vis[N];
void dfs(int x, NetworkFlow::Graph &G1) {
    for (int i = G1.head[x]; ~i; i = G1.edge[i].nxt) {
        G1.head[x] = i;
        auto &e    = G1.edge[i];
        if (vis[e.w]) {
            continue;
        }
        vis[e.w] = 1;
        dfs(e.v, G1);
        st[++top] = e.w;
    }
}
void solve(int ans) {
    NetworkFlow::Graph G1;
    G1.clear();
    check(ans);
    for (int i = 1; i <= m; ++i) {
        if (e[i].w1 <= ans && e[i].w2 <= ans) {
            if (G.edge[id[i]].w == 0) {
                G1.add(e[i].v, e[i].u, i);
                // printf("%d %d %d\n", e[i].v, e[i].u, i);
            } else {
                G1.add(e[i].u, e[i].v, i);
                // printf("%d %d %d\n", e[i].u, e[i].v, i);
            }
        } else if (e[i].w1 <= ans) {
            G1.add(e[i].u, e[i].v, i);
            // printf("%d %d %d\n", e[i].u, e[i].v, i);
        } else if (e[i].w2 <= ans) {
            G1.add(e[i].v, e[i].u, i);
            // printf("%d %d %d\n", e[i].v, e[i].u, i);
        }
    }
    dfs(1, G1);
    // cout << top << endl;
    for (int i = top; i >= 1; i--)
        printf("%d ", st[i]);
}
int main() {
    cin >> n >> m;
    deg.resize(n + 4);
    int siz = n;
    int l = 0x3f3f3f3f, r = -1;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    for (int i = 1; i <= m; i++) {
        int w1, w2;
        cin >> e[i].u >> e[i].v >> w1 >> w2;
        used[e[i].u] = used[e[i].v] = 1;
        if (w1 > w2) {
            swap(e[i].u, e[i].v);
            swap(w1, w2);
        }
        siz += merge(e[i].u, e[i].v);
        e[i].w1 = w1;
        e[i].w2 = w2;
        l       = min(l, e[i].w1);
        r       = max(r, e[i].w2);
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            up++;
        }
    }
    if (siz != 1 && siz - up != 1) {
        cout << "NIE" << endl;
    }
    int ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        // cout << mid << endl;
        if (check(mid)) {
            r   = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }
    if (ans == -1) {
        cout << "NIE" << endl;
        return 0;
    }
    cout << ans << endl;
    solve(ans);
    return 0;
}
// Asusetic eru quionours