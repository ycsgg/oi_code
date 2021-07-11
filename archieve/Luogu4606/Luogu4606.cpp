#include <algorithm>
#include <array>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
const int N       = 1e6 + 10;
const int LOG_LIM = 20;
struct Graph {
    vector<int> edge[N];
    int lim;
    void add(int u, int v) {
        edge[u].push_back(v);
    }
    void clear() {
        for (int i = 1; i <= lim; i++) {
            edge[i].clear();
        }
    }
} G, Tr;
array<int, N> dfn, low;
array<bool, N> vis;
int tim, trcnt, top;
array<int, N> st;
int n, m;
void Tarjan(int x, int _f, const Graph &G) {
    dfn[x] = low[x] = ++tim;
    vis[x]          = 1;
    st[++top]       = x;
    for (auto v : G.edge[x]) {
        if (v == _f)
            continue;
        if (!dfn[v]) {
            Tarjan(v, x, G);
            low[x] = min(low[x], low[v]);
        } else if (vis[x]) {
            low[x] = min(low[x], dfn[v]);
            continue;
        }
        if (low[v] == dfn[x]) {
            ++trcnt;
            Tr.add(x, trcnt);
            while (st[top] != v) {
                int q  = st[top];
                vis[q] = 0;
                Tr.add(trcnt, q);
                top--;
            }
            vis[v] = 0;
            Tr.add(trcnt, v);
            top--;
        } else if (low[v] > dfn[x]) {
            Tr.add(x, v);
            vis[v] = 0;
            top--;
        }
    }
}
int fa[N][LOG_LIM + 1];
array<int, N> dis, dep;
void dfs(int x, const Graph &G) {
    dfn[x] = ++tim;
    for (int i = 1; i <= LOG_LIM; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }
    for (auto v : G.edge[x]) {
        if (v == fa[x][0])
            continue;
        fa[v][0] = x;
        dep[v]   = dep[x] + 1;
        dis[v]   = dis[x] + (v <= n);
        dfs(v, G);
    }
}
int LCA(int u, int v) {
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    for (int i = LOG_LIM; ~i; i--) {
        if (dep[fa[u][i]] >= dep[v]) {
            u = fa[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = LOG_LIM; ~i; i--) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}
int get_dis(int u, int v) {
    int lca = LCA(u, v);
    return dis[u] + dis[v] - 2 * dis[lca];
}
int T;
void clear() {
    low.fill(0);
    dfn.fill(0);
    G.clear();
    Tr.clear();
    dis[0] = dep[0] = 0;
    tim             = 0;
    top             = 0;
}
int main() {
    cin >> T;
    while (T--) {
        cin >> n >> m;
        G.lim = n;
        trcnt = n;
        for (int i = 1; i <= m; i++) {
            int x, y;
            cin >> x >> y;
            G.add(x, y);
            G.add(y, x);
        }
        Tarjan(1, 0, G);
        tim = 0;
        dfs(1, Tr);
        Tr.lim = trcnt;
        int q;
        cin >> q;
        while (q--) {
            int cnt;
            cin >> cnt;
            vector<int> s(cnt);
            for (auto &v : s) {
                cin >> v;
            }
            sort(s.begin(), s.end(), [&](const int &a, const int &b) -> bool {
                return dfn[a] < dfn[b];
            });
            int ans = 0;
            s.push_back(s[0]);
            for (int i = 0; i < cnt; i++) {
                ans += get_dis(s[i], s[i + 1]);
            }
            ans /= 2;
            ans -= cnt;
            ans += (LCA(s[0], s[cnt - 1]) <= n);
            cout << ans << endl;
        }
        clear();
    }
}
// 虚树的dfs序应该是圆方树的！！！ WA * 2
//Asusetic eru quionours.